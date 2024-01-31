// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

namespace Ak
{
	template<typename T, typename ... Args>
	inline T* MemAlloc(Args&& ... args)
	{
		T* ptr = static_cast<T*>(Core::Memory::Internal::Alloc(sizeof(T), std::is_class<T>::value));
		if constexpr(std::is_class<T>::value)
			::new ((void*)ptr) T(std::forward<Args>(args)...);
		return ptr;
	}

	template<typename T = void>
	inline T* MemAllocSize(std::size_t size)
	{
		return static_cast<T*>(Core::Memory::Internal::Alloc(size, true /* Just to make sure it will be allocated in jam allocator */ ));
	}

	template<typename T>
	inline void MemFree(T* ptr)
	{
		if constexpr(std::is_class<T>::value)
			ptr->~T();
		Core::Memory::Internal::Dealloc(static_cast<void*>(ptr));
	}
}
