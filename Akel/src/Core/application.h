// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 12/08/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Core/Components/components.h>
#include <Platform/input.h>
#include <Modules/ImGui/imgui_component.h>
#include <Utils/utils.h>
#include <Core/paths.h>

namespace Ak
{
	class Application : public ComponentStack
	{
		public:
			Application(const char* name = "application");
			void run();
			~Application();

		private:
			const char* _name = "";
	};
}

#endif // __AK_APPLICATION__
