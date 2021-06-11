// This file is a part of Akel
// CREATED : 10/06/2021
// UPDATED : 10/06/2021

#include <Core/core.h>
#include <Utils/Containers/duetsArray.h>

namespace Ak
{
	Application::Application(const std::string& name)
	{
		_name = name;
		_components[WINDOW] = DEFAULT;
		_components[INPUT] = DEFAULT;
		_components[CAM_2D] = DEFAULT;
		_components[CAM_3D] = DEFAULT;
	}

	decltype(auto) Application::getComponent(Components component)
	{
		return _components[component];
	}
}

