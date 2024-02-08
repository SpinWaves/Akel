// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/02/2024
// Updated : 08/02/2024

#pragma once
#include <Core/Application.h>

namespace Ak
{
	template<typename T>
	void Application::LoadEngineModule()
	{
		static_assert(std::is_base_of_v<Module, T>, "invalid engine module");
		if(T::IsInit())
			return;
		m_modules.push_back(new T());
		T::Dependencies::ForEach([this](auto t)
		{
			this->LoadEngineModule<typename decltype(t)::type>();
		});
	}
}
