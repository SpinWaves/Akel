// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_COMPONENT_STACK_H
#define AK_CORE_COMPONENT_STACK_H

#include <Core/PreCompiled.h>
#include <Core/ComponentBase.h>
#include <Core/Memory/MemoryManager.h>

namespace Ak
{
	class AK_CORE_API ComponentStack
	{
		public:
			using iterator = std::vector<ComponentBase*>::iterator;
			using const_iterator = std::vector<ComponentBase*>::const_iterator;
			using reverse_iterator = std::vector<ComponentBase*>::reverse_iterator;
			using const_reverse_iterator = std::vector<ComponentBase*>::const_reverse_iterator;

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

			inline iterator begin() { return m_components.begin(); }
			inline iterator end() { return m_components.end(); }
			inline reverse_iterator rbegin() { return m_components.rbegin(); }
			inline reverse_iterator rend() { return m_components.rend(); }

			inline const_iterator cbegin() { return m_components.cbegin(); }
			inline const_iterator cend() { return m_components.cend(); }
			inline const_reverse_iterator crbegin() { return m_components.crbegin(); }
			inline const_reverse_iterator crend() { return m_components.crend(); }

			void Destroy();

			virtual ~ComponentStack() = default;

		protected:
			std::vector<ComponentBase*> m_components;
	};
}

#include <Core/ComponentStack.inl>

#endif
