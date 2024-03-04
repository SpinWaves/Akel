// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/03/2024
// Updated : 04/03/2024

#ifndef __AK_CORE_SHARED_PTR__
#define __AK_CORE_SHARED_PTR__

#include <Core/PreCompiled.h>

namespace Ak
{
	template <typename T>
	class SharedPtr
	{
		public:
			explicit SharedPtr(T* ptr = nullptr) noexcept;
			SharedPtr(std::nullptr_t) = default;
			SharedPtr(const SharedPtr& ptr) noexcept;
			SharedPtr(SharedPtr&& ptr) noexcept;

			inline SharedPtr operator=(SharedPtr ptr) noexcept;
			inline SharedPtr operator=(T* ptr) noexcept;

			inline T& operator*() const noexcept;
			inline T* operator->() const noexcept;

			inline explicit operator bool() const noexcept;

			inline std::size_t UseCount() const noexcept;
			inline void Reset() noexcept;
			inline T* Get() const noexcept;

			inline void Swap(const SharedPtr& ptr) noexcept;

			~SharedPtr() noexcept;
		
		private:
			struct RefCounter
			{
				T* ptr;
				std::uint32_t count;
			};

		private:
			RefCounter* m_ref = nullptr;
			T* m_ptr = nullptr;
	};

	template <typename T, typename ... Args>
	inline SharedPtr<T> MakeShared(Args&& ... args) noexcept;
}

#include <Core/Memory/SharedPtr.inl>

#endif
