// This file is a part of the Akel editor
// CREATED : 20/07/2021
// UPDATED : 26/07/2021

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size)
    {
        if(_heap != nullptr)
            return;
        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&internalJam::utex);
		#endif

        lockThreads(internalJam::mutex);

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

        unlockThreads(internalJam::mutex);
    }

    void JamAllocator::resize(size_t Size)
    {
        lockThreads(internalJam::mutex);

        _heap = realloc(_heap, Size);
        _heapSize = Size;
        _nMaxDesc = Ak_uint(sqrt(Size) * 2);
        _end = (char*)_heap + _heapSize - (static_cast<size_t>(_nMaxDesc) * 2 * sizeof(Block));
        _freeDesc = static_cast<Block*>(_freeDesc + ((_nMaxDesc - _nUsedDesc) * sizeof(Block)));

        unlockThreads(internalJam::mutex);
    }

    bool JamAllocator::canHold(size_t Size)
    {
        if(Size > _heapSize - _memUsed)
            return false;
        return true;
    }

    void JamAllocator::autoResize(bool set)
    {
        _autoResize = set;
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
        lockThreads(internalJam::mutex);

        std::free(_heap);
        _heap = nullptr;

        unlockThreads(internalJam::mutex);

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            DeleteCriticalSection(&internalJam::mutex);
        #endif
    }

    bool JamAllocator::contains(void* ptr)
    {
    	if(ptr > _heap && ptr < _end)
    		return true;
    	return false;
    }

    JamAllocator::~JamAllocator()
    {
        if(_heap != nullptr)
            destroy();
    }
}
