// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/03/2024
// Updated : 04/03/2024

#ifndef __AK_CORE_UNIQUE_PTR__
#define __AK_CORE_UNIQUE_PTR__

#include <Core/PreCompiled.h>

namespace Ak
{
	template <typename T>
	class UniquePtr
	{
		public:
			constexpr UniquePtr() noexcept;
			constexpr UniquePtr(std::nullptr_t) noexcept;
			explicit UniquePtr(T* ptr) noexcept;
			UniquePtr(UniquePtr&& ptr) noexcept;
			UniquePtr(const UniquePtr& ptr) = delete;

			inline T* Get() const noexcept;

			inline void Swap(const UniquePtr<T>& ptr) noexcept;

			inline void Reset(T* ptr = nullptr) noexcept;

			inline T* Release() noexcept;

			inline explicit operator bool() const noexcept;

			inline UniquePtr& operator=(UniquePtr&& ptr) noexcept;
			inline UniquePtr& operator=(std::nullptr_t) noexcept;
			inline UniquePtr& operator=(const UniquePtr&) = delete;

			inline T* operator->() const noexcept;
			inline T& operator*() const noexcept;

			~UniquePtr();

		private:
			T* m_ptr = nullptr;
	};

	template <typename T, typename ... Args>
	inline std::enable_if_t<!std::is_array<T>::value, UniquePtr<T>> MakeUnique(Args&& ... args) noexcept;
}

#include <Core/Memory/UniquePtr.inl>

#endif
