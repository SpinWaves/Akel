// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 04/01/2022

#include <Core/Components/components.h>
#include <Core/Memory/memory.h>

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
		for(auto elem : _components)
		{
			if(elem->getName() == name)
				return elem;
		}
	}
	Component* ComponentStack::get_component(size_t index)
	{
		if(index <= _components.size())
			return _components[index];
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
				delete elem;
		}
	}
}
