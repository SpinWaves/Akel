// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#include <Panels/Base/panelStack.h>

void PanelStack::add_panel(Panel* panel)
{
	_panels.push_back(panel);
	panel->onAttach();
}

void PanelStack::remove_panel(Panel* panel)
{
	auto it = std::find(_panels.cbegin(), _panels.cend(), panel);
	if(it != _panels.cend())
	{
		(*it)->onQuit();
		_panels.erase(it);
	}
}
void PanelStack::remove_panel(const char* name)
{
	for(size_t i = 0; i < _panels.size(); i++)
	{
		if(_panels[i]->getName() == name)
		{
			_panels[i]->onQuit();
			_panels.erase(_panels.begin() + i);
			break;
		}
	}
}

Panel* PanelStack::get_panel(const char* name)
{
	for(auto elem : _panels)
	{
		if(!strcmp(elem->getName(), name))
			return elem;
	}
}
Panel* PanelStack::get_panel(size_t index)
{
	if(index <= _panels.size())
		return _panels[index];
	return nullptr;
}

PanelStack::~PanelStack()
{
	bool isCustomAlloc = false;
	for(auto elem : _panels)
	{
		isCustomAlloc = false;
		for(auto& jam : Ak::MemoryManager::accessToControlUnit()->jamStack)
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
			for(auto& fixed : Ak::MemoryManager::accessToControlUnit()->fixedStack)
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
			if(!Ak::Core::ProjectFile::getBoolValue("use_memory_manager"))
				delete elem;
			else
				Ak::Core::log::report(STRONG_WARNING, "Panel Stack: unable to free a panel \"%s\" address(%p), unable to find its allocator", elem->getName(), elem);
		}
	}
}
