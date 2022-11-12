// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/07/2021
// Updated : 12/11/2022

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak
{
    void FixedAllocator::init(size_t blockSize, size_t numBlocks)
    {
        if(_heap != nullptr)
            return;

        size_t Size = blockSize * numBlocks;

        std::unique_lock<std::mutex> watchdog(_mutex);

        _heap = malloc(Size); // Main allocation

        _block_size = blockSize;
        _heap_size = Size;
		_bits.init(numBlocks);

        _allocator_number = MemoryManager::accessToControlUnit()->fixedStack.size();
        std::string key = "fixedAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(std::move(key), Size);
        MemoryManager::accessToControlUnit()->fixedStack.emplace_back(weak_from_this());
    }

    void FixedAllocator::resize(size_t numBlocks)
    {
        std::unique_lock<std::mutex> watchdog(_mutex);

        size_t Size = size_t(_block_size * numBlocks);

        _heap = realloc(_heap, Size);

        _heap_size = Size;

        std::string key = "fixedAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);
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
        if(_heap == nullptr)
            return;

        std::unique_lock<std::mutex> watchdog(_mutex);

        std::free(_heap);
        _heap = nullptr;

        //std::string key = "fixedAllocator_size_" + std::to_string(_allocator_number);
        //Core::ProjectFile::setIntValue(key, _memUsed);
    }

    FixedAllocator::~FixedAllocator()
    {
        destroy();
    }
}
