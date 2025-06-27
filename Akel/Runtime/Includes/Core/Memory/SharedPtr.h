// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#include <Core/PreCompiled.h>

namespace Ak
{
	struct RefCounter
	{
		std::uint32_t count = 0;
		std::uint32_t weaks = 0;
	};

	template <typename T>
	class WeakPtr;

	class SharedPtrBase
	{
		protected:
			SharedPtrBase() = default;
			SharedPtrBase(RefCounter* ref) : p_ref(ref) {}
			SharedPtrBase(const SharedPtrBase& other) : p_ref(other.p_ref) {}

			RefCounter* p_ref = nullptr;
	};

	template <typename T>
	class SharedPtr : public SharedPtrBase
	{
		public:
			template <typename Y>
			explicit SharedPtr(Y* ptr = nullptr) noexcept;
			SharedPtr(std::nullptr_t) noexcept : p_ptr(nullptr) {}
			template <typename Y>
			SharedPtr(const SharedPtr<Y>& ptr) noexcept;
			template <typename Y>
			SharedPtr(SharedPtr<Y>&& ptr) noexcept;
			template <typename Y>
			explicit SharedPtr(const WeakPtr<Y>& weak) noexcept;

			template <typename Y>
			inline SharedPtr operator=(SharedPtr<Y> ptr) noexcept;
			template <typename Y>
			inline SharedPtr operator=(Y* ptr) noexcept;

			inline T& operator*() const noexcept;
			inline T* operator->() const noexcept;

			inline explicit operator bool() const noexcept;

			inline std::size_t UseCount() const noexcept;
			inline void Reset() noexcept;
			inline T* Get() const noexcept;

			inline void Swap(SharedPtr& ptr) noexcept;

			~SharedPtr() noexcept;

		private:
			T* p_ptr = nullptr;
	};

	template <typename T, typename ... Args>
	inline std::enable_if_t<!std::is_array<T>::value, SharedPtr<T>> MakeShared(Args&& ... args) noexcept;

	template <typename T>
	class EnableSharedFromThis
	{
		public:
			EnableSharedFromThis() = default;

			inline SharedPtr<T> SharedFromThis();
			inline SharedPtr<const T> SharedFromThis() const;

			inline WeakPtr<T> WeakFromThis();
			inline WeakPtr<const T> WeakFromThis() const;

			~EnableSharedFromThis() = default;

		private:
			mutable WeakPtr<T> m_weak_this;
	};
}

#include <Core/Memory/SharedPtr.inl>
