// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 06/07/2021

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

			virtual void onAttach() {};
			virtual void update() {};
			virtual void onImGuiRender() {};
			virtual void onEvent(Input& input) {};
			virtual void onQuit() {};

			const char* getName();
			~Component() = default;

		protected:
			const char* _name;
	};
}

#endif // __AK_BASE_COMPONENT__

