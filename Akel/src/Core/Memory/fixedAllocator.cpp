// This file is a part of Akel
// CREATED : 19/07/2021
// UPDATED : 22/09/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak
{
    void FixedAllocator::init(size_t blockSize, size_t numBlocks)
    {
        if(_heap != nullptr)
            return;

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&mutex);
		#endif

        size_t Size = blockSize * numBlocks;

        _heap = malloc(Size); // Main allocation

        _block_size = blockSize;
        _heap_size = Size;
        _bits.resize(numBlocks, false);

        lockThreads(mutex);

        _allocator_number = MemoryManager::accessToControlUnit()->fixedStack.size();
        std::string key = "fixedAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);
        MemoryManager::accessToControlUnit()->fixedStack.emplace_back(this);

        unlockThreads(mutex);
    }

    void FixedAllocator::resize(size_t numBlocks)
    {
        lockThreads(mutex);

        size_t Size = size_t(_block_size * numBlocks);

        _heap = realloc(_heap, Size);

        _heap_size = Size;
        _bits.resize(numBlocks, false);

        unlockThreads(mutex);

        std::string key = "fixedAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);
    }

    bool FixedAllocator::canAlloc()
    {
        _it = std::find(_bits.rbegin(), _bits.rend(), true);
        if(_it != _bits.rend())
            return false;
        return true;
    }

    void FixedAllocator::autoResize(bool set)
    {
        _autoResize = set;
    }

    bool FixedAllocator::contains(void* ptr) const
    {
        const uintptr_t ptrAddress = reinterpret_cast<uintptr_t>(ptr);
        const uintptr_t startAddress = reinterpret_cast<uintptr_t>(_heap);
        const uintptr_t endAddress = reinterpret_cast<uintptr_t>(_heap) + _heap_size;
        if(ptrAddress > startAddress && ptrAddress < endAddress)
        	return true;
        return false;
    }

    void FixedAllocator::destroy()
    {
        lockThreads(mutex);

        std::free(_heap);
        _heap = nullptr;

        unlockThreads(mutex);

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            DeleteCriticalSection(&mutex);
        #endif

        //std::string key = "fixedAllocator_size_" + std::to_string(_allocator_number);
        //Core::ProjectFile::setIntValue(key, _memUsed);
    }

    FixedAllocator::~FixedAllocator()
    {
        if(_heap != nullptr)
            destroy();
    }
}
