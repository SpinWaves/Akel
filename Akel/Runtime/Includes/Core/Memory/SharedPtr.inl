// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/03/2024
// Updated : 04/03/2024

#pragma once
#include <Core/Memory/SharedPtr.h>

#include <Core/Memory/MemoryManager.h>
#include <utility>

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
		if(m_ref->count == 0)
			MemFree(m_ref->ptr);
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
}
