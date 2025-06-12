// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_COMPONENT_BASE_H
#define AK_CORE_COMPONENT_BASE_H

#include <Core/PreCompiled.h>

namespace Ak
{
	class AK_CORE_API ComponentBase
	{
		public:
			ComponentBase() = delete;
			ComponentBase(std::string name) : m_name(std::move(name)) {}

			virtual void OnAttach() {}
			virtual void OnUpdate(float delta) {}
			virtual void OnFixedUpdate() {}
			virtual void OnRender() {}
			virtual void OnEvent([[maybe_unused]] class Inputs& inputs) {}
			virtual void OnQuit() {}

			inline const std::string& GetName() const { return m_name; }
			virtual ~ComponentBase() = default;

		protected:
			std::string m_name;
	};
}

#endif
