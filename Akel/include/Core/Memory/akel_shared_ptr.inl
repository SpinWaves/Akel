// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/09/2023
// Updated : 15/09/2023

#include <Core/Memory/akel_shared_ptr.h>

namespace Ak
{
	template <typename T>
	SharedPtr<T>::SharedPtr(T* ptr) noexcept : _ptr(ptr)
	{
		auto it = _refs.find(static_cast<void*>(ptr));
		if(it == _refs.end())
		{
			_ref = new RefCount(1, 0);
			_refs[static_cast<void*>(ptr)] = _ref;
		}
		else
			_ref = it->second;
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) noexcept : _ptr(other._ptr), _ref(other._ref)
	{
		if(_ptr && _ref)
			++_ref->shared;
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept : _ptr(other._ptr), _ref(other._ref)
	{
		++_ref->shared;
	}

	template <typename T>
	SharedPtr<T>& SharedPtr<T>::operator=(std::nullptr_t other) noexcept
	{
	}

	template <typename T>
	SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) noexcept
	{
	}

	template <typename T>
	SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept
	{
	}

	template <typename T>
	SharedPtr<T>::operator bool() const noexcept
	{
		return _ptr != nullptr;
	}

	template <typename T>
	bool SharedPtr<T>::operator==(const SharedPtr<T>& other) noexcept
	{
	}

	template <typename T>
	bool SharedPtr<T>::operator==(T* ptr) noexcept
	{
	}

	template <typename T>
	T& SharedPtr<T>::operator*() noexcept
	{
		return *_ptr;
	}

	template <typename T>
	T* SharedPtr<T>::operator->() noexcept
	{
		return _ptr;
	}

	template <typename T>
	T* SharedPtr<T>::get() noexcept
	{
		return _ptr;
	}

	template <typename T>
	void SharedPtr<T>::swap(SharedPtr<T>& other) noexcept
	{
		T* tmptr = _ptr;
		RefCount* tmpref = _ref;
		_ptr = other._ptr;
		_ref = other._ref;
		other._ptr = tmptr;
		other._ref = tmpref;
	}

	template <typename T>
	void SharedPtr<T>::reset(T* ptr) noexcept
	{
	}

	template <typename T>
	SharedPtr<T>::~SharedPtr()
	{
	}
}
