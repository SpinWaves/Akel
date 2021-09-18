// This file is a part of Akel
// CREATED : 20/07/2021
// UPDATED : 18/09/2021

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size)
    {
        if(_heap != nullptr)
            return;

        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&mutex);
        #endif

        _heap = malloc(Size);
        _heapSize = Size;
        _memUsed = 0;

        _freeSpaces.clear();
        _usedSpaces.clear();

        lockThreads(mutex);

        _allocator_number = MemoryManager::accesToControlUnit()->jamStack.size();
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);
        MemoryManager::accesToControlUnit()->jamStack.push_back(this);

        unlockThreads(mutex);
    }

    void JamAllocator::resize(size_t Size)
    {
        lockThreads(mutex);


        //_heapSize = Size;
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);

        unlockThreads(mutex);
    }

    forceinline bool JamAllocator::canHold(size_t Size)
    {
        if(Size > _heapSize - _memUsed)
            return false;
        return true;
    }

    forceinline void JamAllocator::autoResize(bool set)
    {
        _autoResize = set;
    }

    void JamAllocator::destroy()
    {
        lockThreads(mutex);

        std::free(_heap);
        _heap = nullptr;

        unlockThreads(mutex);

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            DeleteCriticalSection(&mutex);  // Not thread safe ! TODO !!
        #endif

        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, _memUsed);
    }

    forceinline bool JamAllocator::contains(void* ptr)
    {
    	if(ptr > _heap && ptr < (void*)(reinterpret_cast<uintptr_t>(_heap) + _heapSize))
    		return true;
    	return false;
    }

    JamAllocator::~JamAllocator()
    {
        if(_heap != nullptr)
            destroy();
    }
}
