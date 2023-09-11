// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/08/2021
// Updated : 11/09/2023

namespace Ak
{
    void Error(std::string message, ...);
    void Warning(std::string message, ...);

    template<typename T, typename ... Args>
    T* FixedAllocator::alloc(Args&& ... args)
    {
        if(!canAlloc())
        {
            if(!_autoResize)
            {
                Error("Fixed Allocator: unable to alloc block, no more block free");
                return nullptr;
            }
        }
		if(sizeof(T) > _block_size)
		{
			Error("Fixed Allocator: unable to alloc block (size required is greater than a block size, %d)", sizeof(T));
			return nullptr;
		}
        std::unique_lock<std::mutex> watchdog(_mutex);
		size_t index = _bits.getFirstTrueBit();
		_bits.set(index, 0);
		watchdog.unlock();
        if constexpr(std::is_class<T>::value)
        {
            T* ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * index);
            ::new ((void*)ptr) T(std::forward<Args>(args)...);
            return ptr;
        }
		return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * index);
    }

    template<typename T>
    T* FixedAllocator::alloc(size_t size)
    {
        if(!canAlloc())
        {
            if(!_autoResize)
            {
                Error("Fixed Allocator: unable to alloc block, no more block free");
                return nullptr;
            }
        }
		if(size > _block_size)
		{
			Error("Fixed Allocator: unable to alloc block (size required is greater than a block size, %d)", size);
			return nullptr;
		}
        std::unique_lock<std::mutex> watchdog(_mutex);
		size_t index = _bits.getFirstTrueBit();
		_bits.set(index, 0);
		watchdog.unlock();
		return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * index);
    }

    template <class T>
    void FixedAllocator::free(T* ptr)
    {
        if(!contains(ptr))
        {
            Warning("Fixed Allocator: a pointer allocated by another allocator will be freed, this may be an error");
            return;
        }
        if constexpr(std::is_class<T>::value)
            ptr->~T();
        const size_t index = (reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(_heap)) / _block_size;
        std::unique_lock<std::mutex> watchdog(_mutex);
        _bits.set(index, 1);
		watchdog.unlock();
    }
}
