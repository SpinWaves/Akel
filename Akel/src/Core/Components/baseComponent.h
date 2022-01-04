// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 04/01/2022

#ifndef __AK_BASE_COMPONENT__
#define __AK_BASE_COMPONENT__

#include <Akpch.h>
#include <Platform/input.h>

namespace Ak
{
	class Component
	{
		public:
			Component(const char* name = "Component");

			virtual void onAttach();
			virtual void update();
			virtual void onRender();
			virtual void onImGuiRender();
			virtual void onEvent(Input& input);
			virtual void onQuit();

			inline constexpr const char* getName() noexcept { return _name; }
			virtual ~Component();

		protected:
			const char* _name;
	};
}

#endif // __AK_BASE_COMPONENT__
