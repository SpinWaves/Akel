// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/Memory/UniquePtr.h>
#include <Core/Memory/MemoryManager.h>
#include <utility>

namespace Ak
{
	template <typename T>
	constexpr UniquePtr<T>::UniquePtr() noexcept {}

	template <typename T>
	constexpr UniquePtr<T>::UniquePtr(std::nullptr_t) noexcept {}
	
	template <typename T>
	UniquePtr<T>::UniquePtr(T* ptr) noexcept
	{
		if(m_ptr != nullptr)
			MemFree(m_ptr);
		m_ptr = ptr;
	}

	template <typename T>
	UniquePtr<T>::UniquePtr(UniquePtr&& ptr) noexcept
	{
		if(m_ptr != nullptr)
			MemFree(m_ptr);
		m_ptr = ptr.m_ptr;
		ptr.m_ptr = nullptr;
	}

	template <typename T>
	T* UniquePtr<T>::Get() const noexcept
	{
		return m_ptr;
	}

	template <typename T>
	void UniquePtr<T>::Swap(const UniquePtr<T>& ptr) noexcept
	{
		std::swap(m_ptr, ptr.m_ptr);
	}

	template <typename T>
	void UniquePtr<T>::Reset(T* ptr) noexcept
	{
		if(m_ptr != nullptr)
			MemFree(m_ptr);
		m_ptr = ptr;
	}

	template <typename T>
	T* UniquePtr<T>::Release() noexcept
	{
		T* temp = m_ptr;
		m_ptr = nullptr;
		return temp;
	}

	template <typename T>
	UniquePtr<T>::operator bool() const noexcept
	{
		return m_ptr != nullptr;
	}

	template <typename T>
	UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& ptr) noexcept
	{
		Reset(ptr.Release());
		return *this;
	}

	template <typename T>
	UniquePtr<T>& UniquePtr<T>::operator=(std::nullptr_t) noexcept
	{
		Reset(nullptr);
	}

	template <typename T>
	T* UniquePtr<T>::operator->() const noexcept
	{
		return m_ptr;
	}
	
	template <typename T>
	T& UniquePtr<T>::operator*() const noexcept
	{
		return *m_ptr;
	}

	template <typename T>
	UniquePtr<T>::~UniquePtr()
	{
		if(m_ptr != nullptr)
			MemFree(m_ptr);
	}

	template <typename T, typename ... Args>
	std::enable_if_t<!std::is_array<T>::value, UniquePtr<T>> MakeUnique(Args&& ... args) noexcept
	{
		return UniquePtr<T>(MemAlloc<T>(std::forward<Args>(args)...));
	}
}
