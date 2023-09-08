// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/07/2021
// Updated : 08/09/2023

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

		auto control_unit = Core::memory::internal::getControlUnit();
        _allocator_number = control_unit->fixedStack.size();
        std::string key = "fixedAllocator_size_" + std::to_string(_allocator_number);
        getMainAppProjectFile().archive()[std::move(key)] = Size;
    	control_unit->fixedStack.emplace_back(weak_from_this());
    }

    void FixedAllocator::resize(size_t numBlocks)
    {
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
        //getMainAppProjectFile().setIntValue(key, _memUsed);
    }

    FixedAllocator::~FixedAllocator()
    {
        destroy();
    }
}
