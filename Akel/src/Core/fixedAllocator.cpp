// This file is a part of the Akel editor
// CREATED : 19/07/2021
// UPDATED : 21/07/2021

#include <Core/core.h>

namespace Ak
{
    void FixedAllocator::init(size_t blockSize, size_t numBlocks)
    {
        size_t Size = blockSize * numBlocks;

        _heap = malloc(Size); // Main allocation

        _block_size = blockSize;
        _heap_size = Size;
        _bits.resize(numBlocks, false);
    }

    void FixedAllocator::resize(size_t numBlocks)
    {
        size_t Size = size_t(_block_size * numBlocks);

        _heap = realloc(_heap, Size);

        _heap_size = Size;
        _bits.resize(numBlocks, false);
    }

    void* FixedAllocator::alloc()
    {
        std::vector<bool>::iterator it;
        if((it = std::find(_bits.begin(), _bits.end(), false)) == _bits.end())
        {
            Core::log::report(ERROR, "Fixed Allocator: unable to alloc block, no more block free");
            return nullptr;
        }
        *it = true;
        return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * std::distance(_bits.begin(), it));
    }

    void FixedAllocator::free(void* ptr)
    {
        const size_t index = (reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(_heap)) / _block_size;
        _bits[index] = false;
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
        std::free(_heap);
        _heap = nullptr;
    }

    FixedAllocator::~FixedAllocator()
    {
        if(_heap != nullptr)
            destroy();
    }
}
