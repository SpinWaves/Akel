// This file is a part of Akel
// CREATED : 20/07/2021
// UPDATED : 09/09/2021

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size)
    {
        if(_heap != nullptr)
            return;

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&mutex);
        #endif

        _heap = malloc(Size);
        _heapSize = Size;
        _memUsed = 0;
        _end = (char*)_heap + _heapSize;
        _allocOffsets.clear();

        lockThreads(mutex);

        allAllocs.push_back(this);
        _allocator_number = allAllocs.size();
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);

        unlockThreads(mutex);
    }

    void JamAllocator::resize(size_t Size)
    {
        lockThreads(mutex);

        _heap = realloc(_heap, Size);
        _heapSize = Size;
        _end = (char*)_heap + _heapSize;

        unlockThreads(mutex);

        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);
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
        lockThreads(mutex);

        std::free(_heap);
        _heap = nullptr;

        unlockThreads(mutex);

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            DeleteCriticalSection(&mutex);
        #endif

        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, _memUsed);
    }

    bool JamAllocator::contains(void* ptr)
    {
    	if(ptr > _heap && ptr < _end)
    		return true;
    	return false;
    }

    void JamAllocator::add_block(block* newBlock)
    {
    	newBlock->next = nullptr;
        if(_head == nullptr)
    	{
    		_head = newBlock;
    		_tail = _head;
    	}
    	else
    	{
            _tail->next = newBlock;
    		_tail = newBlock;
    	}
    }

    JamAllocator::~JamAllocator()
    {
        if(_heap != nullptr)
            destroy();
    }
}
