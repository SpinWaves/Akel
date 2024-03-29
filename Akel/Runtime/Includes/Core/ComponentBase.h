// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 11/02/2024

#ifndef __AK_CORE_COMPONENT_BASE__
#define __AK_CORE_COMPONENT_BASE__

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
