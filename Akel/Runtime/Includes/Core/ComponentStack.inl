// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 08/02/2024

#pragma once
#include <Core/ComponentStack.h>

namespace Ak
{
	template<typename T, typename ... Args>
	T& ComponentStack::AddComponent(Args&& ... args)
	{
		return static_cast<T&>(AddComponent(MemAlloc<T>(std::forward<Args>(args)...)));
	}

	ComponentBase* ComponentStack::GetComponent(std::size_t index)
	{
		return index < m_components.size() ? m_components[index] : nullptr;
	}

	template<typename T>
	T ComponentStack::GetComponentAs(const std::string& name)
	{
		static_assert(!std::is_pointer_v<T>, "Components can only be casted to pointers");
		return static_cast<T>(GetComponent(name));
	}
	
	template<typename T>
	T ComponentStack::GetComponentAs(std::size_t index)
	{
		static_assert(!std::is_pointer_v<T>, "Components can only be casted to pointers");
		return static_cast<T>(GetComponent(index));
	}
}
