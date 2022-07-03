// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 03/07/2022

#include <Core/Components/components.h>
#include <Core/Memory/memory.h>
#include <Core/log.h>

namespace Ak
{
	void ComponentStack::add_component(Component* component)
	{
		_components.push_back(component);
		component->onAttach();
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
		for(auto elem : _components)
		{
			if(std::strcmp(elem->getName(), name) == 0)
				return elem;
		}
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
			{
				if(!Core::ProjectFile::getBoolValue("use_memory_manager"))
					::delete elem;
				else
					Core::log::report(STRONG_WARNING, "Component Stack: unable to free a component \"%s\" address(%p), unable to find its allocator", elem->getName(), elem);
			}
		}
	}
}
