// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/Memory/SharedPtr.h>

#include <Core/Memory/MemoryManager.h>

namespace Ak
{
	template <typename T>
	SharedPtr<T>::SharedPtr(T* ptr) noexcept : m_ptr(ptr), m_ref(MemAlloc<RefCounter>())
	{
		m_ref->ptr = ptr;
		if(ptr)
			m_ref->count++;
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(const SharedPtr& ptr) noexcept : m_ref(ptr.m_ref), m_ptr(ptr.m_ptr)
	{
		if(m_ref)
			m_ref->count++;
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(SharedPtr&& ptr) noexcept : m_ptr(ptr.m_ptr), m_ref(ptr.m_ref)
	{
		ptr.m_ptr = nullptr;
		ptr.m_ref = nullptr;
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(const WeakPtr<T>& weak) noexcept : m_ptr(weak.m_ptr), m_ref(weak.m_ref)
	{
		if(m_ref)
			m_ref->count++;
	}

	template <typename T>
	SharedPtr<T> SharedPtr<T>::operator=(SharedPtr ptr) noexcept
	{
		ptr.Swap(*this);
		return *this;
	}

	template <typename T>
	SharedPtr<T> SharedPtr<T>::operator=(T* ptr) noexcept
	{
		SharedPtr<T> tmp(ptr);
		tmp.Swap(*this);
		return *this;
	}

	template <typename T>
	void SharedPtr<T>::Swap(const SharedPtr<T>& ptr) noexcept
	{
		std::swap(m_ptr, ptr.m_ptr);
		std::swap(m_ref, ptr.m_ref);
	}

	template <typename T>
	T& SharedPtr<T>::operator*() const noexcept
	{
		return *m_ptr;
	}

	template <typename T>
	T* SharedPtr<T>::operator->() const noexcept
	{
		return m_ptr;
	}

	template <typename T>
	SharedPtr<T>::operator bool() const noexcept
	{
		return m_ptr != nullptr;
	}

	template <typename T>
	std::size_t SharedPtr<T>::UseCount() const noexcept
	{
		return (m_ref) ? m_ref->count : 0;
	}

	template <typename T>
	void SharedPtr<T>::Reset() noexcept
	{
		m_ptr = nullptr;
		if(m_ref)
			m_ref->count--;
		if(m_ref->count <= 0 && m_ref->weaks <= 0)
		{
			MemFree(m_ref->ptr);
			m_ref = nullptr;
		}
	}

	template <typename T>
	T* SharedPtr<T>::Get() const noexcept
	{
		return m_ptr;
	}

	template <typename T>
	SharedPtr<T>::~SharedPtr() noexcept
	{
		if(m_ptr)
			Reset();
	}

	template <typename T, typename ... Args>
	std::enable_if_t<!std::is_array<T>::value, SharedPtr<T>> MakeShared(Args&& ... args) noexcept
	{
		// TODO : do memory contiguous pointer and ref counter allocations
		return SharedPtr<T>(MemAlloc<T>(std::forward<Args>(args)...));
	}

	template <typename T>
	SharedPtr<T> EnableSharedFromThis<T>::SharedFromThis()
	{
		return SharedPtr<T>(m_weak_this);
	}
	
	template <typename T>
	SharedPtr<const T> EnableSharedFromThis<T>::SharedFromThis() const
	{
		return SharedPtr<const T>(m_weak_this);
	}

	template <typename T>
	WeakPtr<T> EnableSharedFromThis<T>::WeakFromThis()
	{
		return m_weak_this;
	}

	template <typename T>
	WeakPtr<const T> EnableSharedFromThis<T>::WeakFromThis() const
	{
		return m_weak_this;
	}
}
