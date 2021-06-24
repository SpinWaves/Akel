// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 24/06/2021

#ifndef __AK_COMPONENTS_STACK__
#define __AK_COMPONENTS_STACK__

#include <Akpch.h>
#include <Core/Components/baseComponent.h>

namespace Ak
{
	class ComponentStack
	{
		public:
			ComponentStack() = default;

			void add_component(Component* component);
			void remove_component(Component* component);	// Modifiers
			void remove_component(const char* name);

			constexpr Component* operator[](const char* name); // Accessor
			constexpr Component* operator[](size_t index);

			std::vector<Component*>::iterator begin()
			{ 
				return _components.begin();
			}
			std::vector<Component*>::iterator end()
			{
				return _components.end();
			}
			std::vector<Component*>::reverse_iterator rbegin()
			{
				return _components.rbegin();
			}
			std::vector<Component*>::reverse_iterator rend()
			{
				return _components.rend();
			}

			std::vector<Component*>::const_iterator begin()
			{
				return _components.cbegin();
			}
			std::vector<Component*>::const_iterator end()
			{
				return _components.cend();
			}
			std::vector<Component*>::const_reverse_iterator crbegin()
			{
				return _components.crbegin();
			}
			std::vector<Component*>::const_reverse_iterator crend()
			{
				return _components.crend();
			}

			~ComponentStack();

		private:
			std::vector<Component*> _components;
	};
}

#endif // __AK_COMPONENTS_STACK__

