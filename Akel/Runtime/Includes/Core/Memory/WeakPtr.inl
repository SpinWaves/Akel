// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/Memory/WeakPtr.h>

namespace Ak
{
	template <typename T>
	WeakPtr<T>::WeakPtr(const WeakPtr<T>& rhs) noexcept : p_ref(rhs.p_ref), p_ptr(rhs.p_ptr)
	{
		if(p_ref)
			p_ref->weaks++;
	}

	template <typename T>
	WeakPtr<T>::WeakPtr(WeakPtr<T>&& rhs) noexcept
	{
		Swap(rhs);
		rhs.Reset();
	}

	template <typename T>
	WeakPtr<T>::WeakPtr(const SharedPtr<T>& shared) noexcept : p_ref(shared.p_ref), p_ptr(shared.p_ptr)
	{
		if(p_ref)
			p_ref->weaks++;
	}

	template <typename T>
	void WeakPtr<T>::Reset() noexcept
	{
		DecrementWeakCount();
		p_ref = nullptr;
		p_ptr = nullptr;
	}

	template <typename T>
	void WeakPtr<T>::Swap(WeakPtr<T>& rhs) noexcept
	{
		std::swap(p_ref, rhs.p_ref);
		std::swap(p_ptr, rhs.p_ptr);
	}

	template <typename T>
	std::size_t WeakPtr<T>::UseCount() const noexcept
	{
		return (p_ref ? p_ref->weaks : 0);
	}

	template <typename T>
	bool WeakPtr<T>::Expired() const noexcept
	{
		return !p_ref || p_ref->count <= 0;;
	}

	template <typename T>
	SharedPtr<T> WeakPtr<T>::Lock() const noexcept
	{
		return (Expired() ? SharedPtr<T>(nullptr) : SharedPtr<T>(*this));
	}

	template <typename T>
	void WeakPtr<T>::DecrementWeakCount() noexcept
	{
		if(p_ref == nullptr)
			return;
		p_ref->weaks--;
		if(p_ref->count <= 0 && p_ref->weaks <= 0)
		{
			MemFree(p_ref);
			p_ref = nullptr;
		}
	}

	template <typename T>
	WeakPtr<T>::~WeakPtr()
	{
		DecrementWeakCount();
	}
}
