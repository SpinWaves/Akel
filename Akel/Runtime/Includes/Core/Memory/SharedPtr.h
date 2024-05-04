// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/03/2024
// Updated : 04/05/2024

#pragma once

#include <Core/PreCompiled.h>

namespace Ak
{
	template <typename T>
	class WeakPtr;

	template <typename T>
	class SharedPtr
	{
		public:
			explicit SharedPtr(T* ptr = nullptr) noexcept;
			SharedPtr(std::nullptr_t) noexcept : m_ref(nullptr), m_ptr(nullptr) {}
			SharedPtr(const SharedPtr& ptr) noexcept;
			SharedPtr(SharedPtr&& ptr) noexcept;
			explicit SharedPtr(const WeakPtr<T>& weak) noexcept;

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
				T* ptr = nullptr;
				std::uint32_t count = 0;
				std::uint32_t weaks = 0;
			};

		private:
			RefCounter* m_ref = nullptr;
			T* m_ptr = nullptr;
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
