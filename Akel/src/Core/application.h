// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 14/06/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Platform/window.h>
#include <Platform/input.h>
#include <Utils/camera.h>
#include <Utils/Containers/duetsArray.h>
#include <Utils/typeFinderTuple.h>

namespace Ak
{
	class Window;
	class Input;
	class Camera3D;

	class Application
	{
		public:
			Application(const std::string name);

			template <typename Comp, typename T>
			void addComponent(T component)
			{
				Comp type;
				static_assert(std::is_same_v<decltype(component), decltype(type)>, "Akel application : the type of the component must be the same as the one specified");
				_components[tuple_element_finder_v<T, decltype(_componentsTypes)>] = component;
			}
			template <typename Comp>
			void addComponent()
			{
				_components[tuple_element_finder_v<Comp, decltype(_componentsTypes)>] = default_t<Comp>::get();
			}

			template <typename T>
			T getComponent()
			{
				return _components[tuple_element_finder_v<T, decltype(_componentsTypes)>];
			}

			virtual ~Application() = default;

		private:
			std::string _name = "";
			std::tuple<Window, Input> _componentsTypes;
			std::array<std::any, std::tuple_size_v<decltype(_componentsTypes)>> _components;
	};
}

#endif // __AK_APPLICATION__

