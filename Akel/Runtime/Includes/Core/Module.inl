// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#include <Core/Logs.h>

namespace Ak
{
	template<typename T>
	Module<T>::Module(std::string name, T* ptr) : m_module_name(std::move(name))
	{
		if(T::s_instance != nullptr)
			Log::FatalError("only one instance of %s can exists at a given time", m_module_name.c_str());
		T::s_instance = pointer;

		Log::Debug("Starting " + m_module_name + "...");
	}

	template<typename T>
	T* Module<T>::Get()
	{
		return T::s_instance;
	}

	template<typename T>
	Module<T>::~Module()
	{
		Log::Debug("Shutdown " + m_module_name);
		T::s_instance = nullptr;
	}
}
