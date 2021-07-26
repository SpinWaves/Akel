// This file is a part of the Akel editor
// CREATED : 25/07/2021
// UPDATED : 26/07/2021

#include <Core/Memory/jamAllocator.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* JamAllocator::alloc(Args&& ... args)
    {
        if(_nUsedDesc == _nMaxDesc)
        {
            if(_autoResize)
                resize(_heapSize * 2);
            else
            {
                Core::log::report(ERROR, "Jam Allocator: Reached maximum number of alloc descriptors, free something to continue");
                return nullptr;
            }
        }
        if(!canHold(sizeof(T)))
        {
            if(_autoResize)
                resize(_heapSize * 2);
            else
            {
                Core::log::report(ERROR, "Jam Allocator: the requested allocation is too large for the allocator, free up memory or increase the size of the allocator");
                return nullptr;
            }
        }

        lockThreads(internalJam::mutex);

        for(size_t i = 0; i < _nFreeDesc; i++)
        {
            if(_freeDesc[i].size > sizeof(T))
            {
                T* ptr = reinterpret_cast<T*>((char*)_heap + static_cast<unsigned int>(_freeDesc[i].offset + _freeDesc[i].size - sizeof(T)));

                unsigned int allocIndex = int(UINT64_MAX);
            	for(unsigned int j = 0; j < _nUsedDesc; j++)
            	{
            		if(_usedDesc[j].offset == 0)
            		{
            			allocIndex = j;
            			break;
            		}
            	}
            	if(allocIndex > _nUsedDesc)
            	{
            		allocIndex = _nUsedDesc;
            		_nUsedDesc++;
            	}
            	_usedDesc[allocIndex].offset = static_cast<unsigned int>(static_cast<unsigned int>(_freeDesc[i].offset + _freeDesc[i].size - sizeof(T)));
            	_usedDesc[allocIndex].size = static_cast<unsigned int>(sizeof(T));

            	_freeDesc[i].size -= static_cast<unsigned int>(sizeof(T));

                unlockThreads(internalJam::mutex);

                if(std::is_class<T>::value)
                    new (ptr) T(std::forward<Args>(args)...);

            	return ptr;
            }
        }

        unlockThreads(internalJam::mutex);
        return nullptr;
    }

    template <typename T = void>
    void JamAllocator::free(T* ptr)
    {
        if(!contains((void*)ptr))
        {
            Core::log::report(ERROR, "Jam Allocator: a pointer allocated by another allocator cannot be freed");
            return;
        }
        if(std::is_class<T>::value)
            ptr->~T();

        lockThreads(internalJam::mutex);

        unsigned int offset = static_cast<unsigned int>(reinterpret_cast<char*>(ptr) - static_cast<char*>(_heap));
    	for(unsigned int i = 0; i < _nUsedDesc; i++)
    	{
    		if(_usedDesc[i].offset == offset)
    		{
    			for(unsigned int j = 0; j < _nFreeDesc; j++)
    			{
    				if(_freeDesc[j].offset == 0)
    				{
    					_freeDesc[j].offset = _usedDesc[i].offset;
    					_freeDesc[j].size = _usedDesc[i].size;
    					_usedDesc[i].offset = 0;
    					collect();

                        unlockThreads(internalJam::mutex);
                        return;
    			    }
    			}
    			if(_nFreeDesc == _nMaxDesc)
    			{
                    Core::log::report(ERROR, "Jam Allocator: Reached maximum number of FREE descriptors, defragmenting");
    				collect();

                    unlockThreads(internalJam::mutex);
                    return;
    			}
    			else
    			{
    				_freeDesc[_nFreeDesc].offset = _usedDesc[i].offset;
    				_freeDesc[_nFreeDesc].size = _usedDesc[i].size;
    				_usedDesc[i].offset = 0;
    				_nFreeDesc++;
    				collect();

                    unlockThreads(internalJam::mutex);
                    return;
    			}
    		}
    	}

        unlockThreads(internalJam::mutex);
    }
}
