// This file is a part of the Akel editor
// CREATED : 19/07/2021
// UPDATED : 22/07/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak
{
    namespace internal
    {
        MutexHandel mutex;
    }

    void FixedAllocator::init(size_t blockSize, size_t numBlocks)
    {
        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&internal::mutex);
		#endif

        lockThreads(internal::mutex);

        size_t Size = blockSize * numBlocks;

        _heap = malloc(Size); // Main allocation

        _block_size = blockSize;
        _heap_size = Size;
        _bits.resize(numBlocks, false);

        unlockThreads(internal::mutex);
    }

    void FixedAllocator::resize(size_t numBlocks)
    {
        lockThreads(internal::mutex);

        size_t Size = size_t(_block_size * numBlocks);

        _heap = realloc(_heap, Size);

        _heap_size = Size;
        _bits.resize(numBlocks, false);

        unlockThreads(internal::mutex);
    }

    void* FixedAllocator::alloc()
    {
        lockThreads(internal::mutex);

        std::vector<bool>::iterator it;
        if((it = std::find(_bits.begin(), _bits.end(), false)) == _bits.end())
        {
            Core::log::report(ERROR, "Fixed Allocator: unable to alloc block, no more block free");
            return nullptr;
        }
        *it = true;

        unlockThreads(internal::mutex);

        return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * std::distance(_bits.begin(), it));
    }

    void FixedAllocator::free(void* ptr)
    {
        lockThreads(internal::mutex);

        const size_t index = (reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(_heap)) / _block_size;
        _bits[index] = false;

        unlockThreads(internal::mutex);
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
        lockThreads(internal::mutex);

        std::free(_heap);
        _heap = nullptr;

        unlockThreads(internal::mutex);

        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            DeleteCriticalSection(&internal::mutex);
        #endif
    }

    FixedAllocator::~FixedAllocator()
    {
        if(_heap != nullptr)
            destroy();
    }
}
