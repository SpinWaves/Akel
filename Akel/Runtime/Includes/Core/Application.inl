// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/02/2024
// Updated : 06/02/2024

#pragma once

#include <Core/Module.h>
#include <Core/Application.h>

namespace Ak
{
	template<typename T>
	void Application::LoadEngineModule()
	{
		using ModuleLoaded = TypeList<>;
		static_assert(std::is_base_of_v<Module, T>, "invalid engine module");
		if constexpr(ModuleLoaded::Has<T>)
			return;
		else
		{
			T::Dependencies::ForEach([this](auto t)
			{
				using Dep = decltype(t);
				this->LoadEngineModule<Dep::type>();
			});
			m_modules.push_back(new T());
			ModuleLoaded::PushBack<T>();
		}
	}
}
