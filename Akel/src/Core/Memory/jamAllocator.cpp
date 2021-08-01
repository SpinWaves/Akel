// This file is a part of Akel
// CREATED : 20/07/2021
// UPDATED : 29/07/2021

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size)
    {
        if(_heap != nullptr)
            return;

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&internalJam::mutex);
        #endif

        lockThreads(internalJam::mutex);

        _heap = malloc(Size);
        _heapSize = Size;
        _memUsed = 0;
        _end = (char*)_heap + _heapSize;

        unlockThreads(internalJam::mutex);
    }

    void JamAllocator::resize(size_t Size)
    {
        lockThreads(internalJam::mutex);

        _heap = realloc(_heap, Size);
        _heapSize = Size;
        _end = (char*)_heap + _heapSize;

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
