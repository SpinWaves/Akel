// This file is a part of Akel
// Author : @kbz_8
// CREATED : 23/06/2021
// UPDATED : 15/02/2022

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

			inline const char* getName() noexcept { return _name.c_str(); }
			inline void setName(const char* name) noexcept { _name = name; }
			virtual ~Component();

		protected:
			std::string _name;
	};
}

#endif // __AK_BASE_COMPONENT__
