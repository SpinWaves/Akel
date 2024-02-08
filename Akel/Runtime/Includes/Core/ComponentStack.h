// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 08/02/2024

#ifndef __AK_CORE_COMPONENT_STACK__
#define __AK_CORE_COMPONENT_STACK__

#include <Core/PreCompiled.h>
#include <Core/ComponentBase.h>
#include <Core/Memory/MemoryManager.h>

namespace Ak
{
	class AK_CORE_API ComponentStack
	{
		public:
			ComponentStack() = default;

			template<typename T, typename ... Args>
			inline T& AddComponent(Args&& ... args);
			ComponentBase& AddComponent(ComponentBase* component);

			void RemoveComponent(ComponentBase* component);
			void RemoveComponent(const std::string& name);

			ComponentBase* GetComponent(const std::string& name);
			inline ComponentBase* GetComponent(std::size_t index);

			template<typename T>
			inline T GetComponentAs(const std::string& name);
			template<typename T>
			inline T GetComponentAs(std::size_t index);

			void Destroy();

			virtual ~ComponentStack() = default;

		protected:
			std::vector<ComponentBase*> m_components;
	};
}

#include <Core/ComponentStack.inl>

#endif
