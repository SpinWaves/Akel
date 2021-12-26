// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 25/12/2021

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

			virtual void onAttach() = 0;
			virtual void update() = 0;
			virtual void onRender() = 0;
			virtual void onImGuiRender() = 0;
			virtual void onEvent(Input& input) = 0;
			virtual void onQuit() = 0;

			const char* getName();
			virtual ~Component() = default;

		protected:
			const char* _name;
	};
}

#endif // __AK_BASE_COMPONENT__
