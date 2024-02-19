// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/02/2024
// Updated : 19/02/2024

#ifndef __AK_UTILS_NON_OWNING_PTR__
#define __AK_UTILS_NON_OWNING_PTR__

namespace Ak
{
	template<typename T>
	class NonOwningPtr
	{
		public:
			NonOwningPtr(T* ptr = nullptr);
			NonOwningPtr(const NonOwningPtr&) = default;
			NonOwningPtr(NonOwningPtr&& ptr) noexcept;

			NonOwningPtr& operator=(T* ptr);
			NonOwningPtr& operator=(const NonOwningPtr&) = default;
			NonOwningPtr& operator=(NonOwningPtr&& ptr) noexcept;

			inline operator bool() const noexcept;

			inline T* Get() const noexcept;
			inline T* operator->() const noexcept;
			inline T& operator*() const noexcept;

			~NonOwningPtr() = default;

		private:
			T* m_ptr = nullptr;
	};
}

#include <Utils/NonOwningPtr.inl>

#endif
