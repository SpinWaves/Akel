// This file is a part of the Akel editor
// CREATED : 20/07/2021
// UPDATED : 20/07/2021

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size)
    {
        _heap = malloc(Size);
        _heapSize = Size;
        _nMaxDesc = Ak_uint(sqrt(Size) * 2);
        _memUsed = 0;
        _end = (char*)_heap + _heapSize - (static_cast<size_t>(_nMaxDesc) * 2 * sizeof(Block));

        // Init Descriptors
        _usedDesc = static_cast<Block*>(_end);
        _nUsedDesc = 0;

        _freeDesc = static_cast<Block*>((void*)((char*)_end + (_nMaxDesc * sizeof(Block))));
        _nFreeDesc = 1;
        _freeDesc[0].offset = 4;
        _freeDesc[0].size = static_cast<int>((char*)_end - (char*)_heap);
    }

    void* JamAllocator::alloc(size_t Size)
    {
        if(_nUsedDesc == _nMaxDesc)
        {
            Core::log::report(ERROR, "Jam Allocator: Reached maximum number of ALLOC descriptors, free something to continue");
            return nullptr;
        }
        for(size_t i = 0; i < _nFreeDesc; i++)
        {
            if(_freeDesc[i].size > Size)
            {
                void* ptr = reinterpret_cast<void*>((char*)_heap + static_cast<unsigned int>(_freeDesc[i].offset + _freeDesc[i].size - Size));

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
            	_usedDesc[allocIndex].offset = static_cast<unsigned int>(static_cast<unsigned int>(_freeDesc[i].offset + _freeDesc[i].size - Size));
            	_usedDesc[allocIndex].size = static_cast<unsigned int>(Size);

            	_freeDesc[i].size -= static_cast<unsigned int>(Size);

            	return ptr;
            }
        }
        return nullptr;
    }

    void JamAllocator::free(void* ptr)
    {
        unsigned int offset = static_cast<unsigned int>(static_cast<char*>(ptr) - static_cast<char*>(_heap));
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
                        return;
    			    }
    			}
    			if(_nFreeDesc == _nMaxDesc)
    			{
                    Core::log::report(ERROR, "Jam Allocator: Reached maximum number of FREE descriptors, defragmenting");
    				collect();
                    return;
    			}
    			else
    			{
    				_freeDesc[_nFreeDesc].offset = _usedDesc[i].offset;
    				_freeDesc[_nFreeDesc].size = _usedDesc[i].size;
    				_usedDesc[i].offset = 0;
    				_nFreeDesc++;
    				collect();
                    return;
    			}
    		}
    	}
    }

    void JamAllocator::collect()
    {
        for(unsigned int i = 0; i < _nFreeDesc; i++)
    	{
    		if(_freeDesc[i].offset != 0)
            {
        		for(unsigned int j = 0; j < _nFreeDesc; j++)
        		{
        			if(_freeDesc[j].offset != 0 && _freeDesc[i].offset + _freeDesc[i].size == _freeDesc[j].offset)
        			{
        				_freeDesc[i].size += _freeDesc[j].size;
        				_freeDesc[j].offset = 0;
        				_freeDesc[j].size = 0;
        			}
        		}
            }
    	}
    }

    void JamAllocator::destroy()
    {
        free(_heap);
        _heap = nullptr;
    }

    JamAllocator::~JamAllocator()
    {
        if(_heap != nullptr)
            destroy();
    }
}
