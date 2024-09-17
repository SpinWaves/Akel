// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/Memory/WeakPtr.h>

namespace Ak
{
	template <typename T>
	WeakPtr<T>::WeakPtr(const WeakPtr<T>& rhs) noexcept : m_ref(rhs.m_ref), m_ptr(rhs.m_ptr)
	{
		if(m_ref)
			m_ref->weaks++;
	}

	template <typename T>
	WeakPtr<T>::WeakPtr(WeakPtr<T>&& rhs) noexcept
	{
		Swap(rhs);
		rhs.Reset();
	}

	template <typename T>
	WeakPtr<T>::WeakPtr(const SharedPtr<T>& shared) noexcept : m_ref(shared.m_ref), m_ptr(shared.m_ptr)
	{
		if(m_ref)
			m_ref->weaks++;
	}

	template <typename T>
	void WeakPtr<T>::Reset() noexcept
	{
		DecrementWeakCount();
		m_ref = nullptr;
		m_ptr = nullptr;
	}

	template <typename T>
	void WeakPtr<T>::Swap(WeakPtr<T>& rhs) noexcept
	{
		std::swap(m_ref, rhs.m_ref);
		std::swap(m_ptr, rhs.m_ptr);
	}

	template <typename T>
	std::size_t WeakPtr<T>::UseCount() const noexcept
	{
		return (m_ref ? m_ref->weaks : 0);
	}

	template <typename T>
	bool WeakPtr<T>::Expired() const noexcept
	{
		return !m_ref || m_ref->count <= 0;;
	}

	template <typename T>
	SharedPtr<T> WeakPtr<T>::Lock() const noexcept
	{
		return (Expired() ? SharedPtr<T>(nullptr) : SharedPtr<T>(*this));
	}

	template <typename T>
	void WeakPtr<T>::DecrementWeakCount() noexcept
	{
		if(m_ref == nullptr)
			return;
		m_ref->weaks--;
		if(m_ref->count <= 0 && m_ref->weaks <= 0)
		{
			MemFree(m_ref);
			m_ref = nullptr;
		}
	}

	template <typename T>
	WeakPtr<T>::~WeakPtr()
	{
		DecrementWeakCount();
	}
}
