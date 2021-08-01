// This file is a part of Akel
// CREATED : 19/07/2021
// UPDATED : 26/07/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak
{
    void FixedAllocator::init(size_t blockSize, size_t numBlocks)
    {
        if(_heap != nullptr)
            return;

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&internalFixed::mutex);
		#endif

        lockThreads(internalFixed::mutex);

        size_t Size = blockSize * numBlocks;

        _heap = malloc(Size); // Main allocation

        _block_size = blockSize;
        _heap_size = Size;
        _bits.resize(numBlocks, false);

        unlockThreads(internalFixed::mutex);
    }

    void FixedAllocator::resize(size_t numBlocks)
    {
        lockThreads(internalFixed::mutex);

        size_t Size = size_t(_block_size * numBlocks);

        _heap = realloc(_heap, Size);

        _heap_size = Size;
        _bits.resize(numBlocks, false);

        unlockThreads(internalFixed::mutex);
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
        lockThreads(internalFixed::mutex);

        std::free(_heap);
        _heap = nullptr;

        unlockThreads(internalFixed::mutex);

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            DeleteCriticalSection(&internalFixed::mutex);
        #endif
    }

    FixedAllocator::~FixedAllocator()
    {
        if(_heap != nullptr)
            destroy();
    }
}
