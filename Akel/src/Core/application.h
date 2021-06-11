// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 11/06/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Platform/platform.h>
#include <Utils/utils.h>

namespace Ak
{
	class Window;
	class Input;
	class Camera3D;
}

enum Components
{
	WINDOW = Ak::Window,
	INPUT = Ak::Input,
	CAM_2D,
	CAM_3D = Ak::Camera3D
};

namespace Ak
{
	class Application
	{
		public:
			Application(const std::string& name);

			template <Components Comp, typename T>
			void addComponent(T component)
			{
				Comp compo;
				if(nullptr == dynamic_cast<T*>(&component))
				{
					std::cout << red << "Akel application : bad component type" << def << std::endl;
					return;
				}
				switch(component)
				{
					case WINDOW: _components[WINDOW] = component; break;
					case INPUT: _components[INPUT] = component; break;
					case CAM_3D: _components[CAM_3D] = component; break;

					default: break;
				}
			}
			template <Components T>
			void addComponent()
			{
				T component;
				switch(component)
				{
					case WINDOW: _components[WINDOW] = Window; break;
					case INPUT: _components[INPUT] = Input; break;
					case CAM_3D: _components[CAM_3D] = Camera3D; break;

					default: break;
				}
			}

			decltype(auto) getComponent(Components component);

			virtual ~Application() = default;

		private:
			std::string _name = "";
			std::unordered_map<Components, std::any> _components;
	};
}

#endif // __AK_APPLICATION__

