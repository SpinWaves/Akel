// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/02/2024
// Updated : 12/02/2024

#pragma once
#include <Core/Application.h>

namespace Ak
{
	constexpr void Application::Quit() noexcept
	{
		m_running = false;
	}

	template<typename T, typename...Args>
	void Application::LoadEngineModule(Args&&... args)
	{
		static_assert(std::is_base_of_v<Module, T>, "invalid engine module");
		if(T::IsInit())
			return;
		m_modules.push_back(new T(std::forward<Args>(args)...));
		T::Dependencies::ForEach([this](auto t)
		{
			this->LoadEngineModule<typename decltype(t)::type>();
		});
	}
}
