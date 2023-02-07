// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 21/12/2022

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
			if(std::strcmp(_components[i]->getName(), name) == 0)
			{
				_components[i]->onQuit();
				_components.erase(_components.begin() + i);
				break;
			}
		}
	}

	Component* ComponentStack::get_component(const char* name)
	{
		auto it = std::find_if(_components.begin(), _components.end(), [=](Component* c) { return std::strcmp(c->getName(), name) == 0; });
		if(it != _components.end())
			return *it;
		return nullptr;
	}

	ComponentStack::~ComponentStack()
	{
		bool isCustomAlloc = false;
		for(auto elem : _components)
		{
			isCustomAlloc = false;
			for(auto& jam : MemoryManager::accessToControlUnit()->jamStack)
			{
				if(!jam.expired())
				{
					if(jam.lock()->contains(elem))
					{
						jam.lock()->free(elem);
						isCustomAlloc = true;
						break;
					}
				}
			}
			if(!isCustomAlloc)
			{
				for(auto& fixed : MemoryManager::accessToControlUnit()->fixedStack)
				{
					if(!fixed.expired())
					{
						if(fixed.lock()->contains(elem))
						{
							fixed.lock()->free(elem);
							isCustomAlloc = true;
							break;
						}
					}
				}
			}
			if(!isCustomAlloc)
				Core::log::report(STRONG_WARNING, "Component Stack: unable to free a component \"%s\" address(%p), unable to find its allocator", elem->getName(), elem);
		}
	}
}
