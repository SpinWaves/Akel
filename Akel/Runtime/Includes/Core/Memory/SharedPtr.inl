// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/Memory/SharedPtr.h>

#include <Core/Memory/MemoryManager.h>

namespace Ak
{
	template <typename T>
	template <typename Y>
	SharedPtr<T>::SharedPtr(Y* ptr) noexcept : SharedPtrBase(MemAlloc<RefCounter>()), p_ptr(ptr)
	{
		if(ptr)
			p_ref->count++;
	}

	template <typename T>
	template <typename Y>
	SharedPtr<T>::SharedPtr(const SharedPtr<Y>& ptr) noexcept : SharedPtrBase(ptr), p_ptr(ptr.Get())
	{
		if(p_ref)
			p_ref->count++;
	}

	template <typename T>
	template <typename Y>
	SharedPtr<T>::SharedPtr(SharedPtr<Y>&& ptr) noexcept : SharedPtrBase(ptr), p_ptr(ptr.Get())
	{
	}

	template <typename T>
	template <typename Y>
	SharedPtr<T>::SharedPtr(const WeakPtr<Y>& weak) noexcept : SharedPtrBase(weak.p_ref), p_ptr(weak.p_ptr)
	{
		if(p_ref)
			p_ref->count++;
	}

	template <typename T>
	template <typename Y>
	SharedPtr<T> SharedPtr<T>::operator=(SharedPtr<Y> ptr) noexcept
	{
		ptr.Swap(*this);
		return *this;
	}

	template <typename T>
	template <typename Y>
	SharedPtr<T> SharedPtr<T>::operator=(Y* ptr) noexcept
	{
		SharedPtr<T> tmp(ptr);
		tmp.Swap(*this);
		return *this;
	}

	template <typename T>
	void SharedPtr<T>::Swap(SharedPtr<T>& ptr) noexcept
	{
		std::swap(p_ptr, ptr.p_ptr);
		std::swap(p_ref, ptr.p_ref);
	}

	template <typename T>
	T& SharedPtr<T>::operator*() const noexcept
	{
		return *p_ptr;
	}

	template <typename T>
	T* SharedPtr<T>::operator->() const noexcept
	{
		return p_ptr;
	}

	template <typename T>
	SharedPtr<T>::operator bool() const noexcept
	{
		return p_ptr != nullptr;
	}

	template <typename T>
	std::size_t SharedPtr<T>::UseCount() const noexcept
	{
		return (p_ref) ? p_ref->count : 0;
	}

	template <typename T>
	void SharedPtr<T>::Reset() noexcept
	{
		if(p_ref)
			p_ref->count--;
		if(p_ref->count <= 0)
		{
			MemFree(p_ptr);
			p_ref = nullptr;
		}
		p_ptr = nullptr;
	}

	template <typename T>
	T* SharedPtr<T>::Get() const noexcept
	{
		return p_ptr;
	}

	template <typename T>
	SharedPtr<T>::~SharedPtr() noexcept
	{
		if(p_ptr)
			Reset();
	}

	template <typename T, typename ... Args>
	std::enable_if_t<!std::is_array<T>::value, SharedPtr<T>> MakeShared(Args&& ... args) noexcept
	{
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
