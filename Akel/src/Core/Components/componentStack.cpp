// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 10/09/2023

#include <Core/Components/components.h>
#include <Core/Memory/memory.h>
#include <Core/log.h>

namespace Ak
{
	Component* ComponentStack::add_component(Component* component)
	{
		_components.push_back(component);
		component->onAttach();
		return component;
	}

	void ComponentStack::remove_component(Component* component)
	{
		auto it = std::find(_components.cbegin(), _components.cend(), component);
		if(it != _components.cend())
		{
			(*it)->onQuit();
			_components.erase(it);
		}
	}

	void ComponentStack::remove_component(const char* name)
	{
		for(size_t i = 0; i < _components.size(); i++)
		{
			if(_components[i]->getName() == name)
			{
				_components[i]->onQuit();
				_components.erase(_components.begin() + i);
				break;
			}
		}
	}

	Component* ComponentStack::get_component(const char* name)
	{
		auto it = std::find_if(_components.begin(), _components.end(), [=](Component* c) { return c->getName() == name; });
		if(it != _components.end())
			return *it;
		return nullptr;
	}

	void ComponentStack::destroy()
	{
		for(Component* elem : _components)
		{
			bool has_been_freed = false;
			for(auto& jam : Core::memory::internal::getControlUnit()->jamStack)
			{
				if(jam.expired())
					continue;
				if(jam.lock()->contains(elem))
				{
					jam.lock()->free(elem);
					has_been_freed = true;
					break;
				}
			}
			if(!has_been_freed)
			{
				for(auto& fixed : Core::memory::internal::getControlUnit()->fixedStack)
				{
					if(fixed.expired())
						continue;
					if(fixed.lock()->contains(elem))
					{
						fixed.lock()->free(elem);
						has_been_freed = true;
						break;
					}
				}
			}
			if(!has_been_freed)
			{
				Core::log::report(STRONG_WARNING, "Component Stack: unable to free a component \"%s\" address(%p), unable to find its allocator", elem->getName().c_str(), elem);
				elem->~Component();
			}
		}
	}
}
