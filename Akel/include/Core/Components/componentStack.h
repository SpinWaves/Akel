// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 07/07/2023

#ifndef __AK_COMPONENTS_STACK__
#define __AK_COMPONENTS_STACK__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
	class Component;
	template <class T = void, typename ... Args>
	T* memAlloc(Args&& ... args);

	class AK_API ComponentStack
	{
		public:
			ComponentStack() = default;

			Component* add_component(Component* component);

			template <typename T, typename ... Args>
			inline T* add_component(Args&& ... args) { return static_cast<T*>(add_component(memAlloc<T>(std::forward<Args>(args)...))); }

			void remove_component(Component* component); // Modifiers
			void remove_component(const char* name);

			Component* get_component(const char* name);  // Accessors
			inline Component* get_component(size_t index) { return index < _components.size() ? _components[index] : nullptr; }

			template <typename T>
			inline T get_component_as(const char* name) { return static_cast<T>(get_component(name)); }
			template <typename T>
			inline T get_component_as(size_t index) { return static_cast<T>(get_component(index)); }

			inline std::vector<Component*>::iterator begin() { return _components.begin(); }
			inline std::vector<Component*>::iterator end() { return _components.end(); }
			inline std::vector<Component*>::reverse_iterator rbegin() { return _components.rbegin(); }
			inline std::vector<Component*>::reverse_iterator rend() { return _components.rend(); }

			inline std::vector<Component*>::const_iterator cbegin() { return _components.cbegin(); }
			inline std::vector<Component*>::const_iterator cend() { return _components.cend(); }
			inline std::vector<Component*>::const_reverse_iterator crbegin() { return _components.crbegin(); }
			inline std::vector<Component*>::const_reverse_iterator crend() { return _components.crend(); }

			virtual ~ComponentStack();

		protected:
			std::vector<Component*> _components;
	};
}

#endif // __AK_COMPONENTS_STACK__

