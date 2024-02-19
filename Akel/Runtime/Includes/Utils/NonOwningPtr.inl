// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/02/2024
// Updated : 19/02/2024

#pragma once
#include <Utils/NonOwningPtr.h>

namespace Ak
{
	template<typename T>
	NonOwningPtr<T>::NonOwningPtr(T* ptr) : m_ptr(ptr) {}
	
	template<typename T>
	NonOwningPtr<T>::NonOwningPtr(NonOwningPtr<T>&& ptr) noexcept : m_ptr(ptr.m_ptr)
	{
		ptr.m_ptr = nullptr;
	}

	template<typename T>
	NonOwningPtr<T>& NonOwningPtr<T>::operator=(T* ptr)
	{
		m_ptr = ptr;
	}
	
	template<typename T>
	NonOwningPtr<T>& NonOwningPtr<T>::operator=(NonOwningPtr&& ptr) noexcept
	{
		m_ptr = ptr.m_ptr;
		ptr.m_ptr = nullptr;
	}

	template<typename T>
	NonOwningPtr<T>::operator bool() const noexcept
	{
		return m_ptr != nullptr;
	}

	template<typename T>
	T* NonOwningPtr<T>::Get() const noexcept
	{
		return m_ptr;
	}
	
	template<typename T>
	T* NonOwningPtr<T>::operator->() const noexcept
	{
		return m_ptr;
	}
	
	template<typename T>
	T& NonOwningPtr<T>::operator*() const noexcept
	{
		return *m_ptr;
	}
}
