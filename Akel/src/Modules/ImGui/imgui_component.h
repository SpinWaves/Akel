// This file is a part of Akel
// CREATED : 03/07/2021
// UPDATED : 26/09/2021

#ifndef __AK_IMGUI_COMPONENT__
#define __AK_IMGUI_COMPONENT__

#include <Akpch.h>
#include <Platform/window.h>

namespace Ak
{
	class ImGuiComponent : public WindowComponent
	{
		public:
			ImGuiComponent(const char* title = "ImGui window");

			void onAttach() override;
			void onEvent(Input& input) override;
			void update() override {}
			void onQuit() override;

			void begin();
			void end();

			static int getNumComp() { return _componentsInit; }

			virtual ~ImGuiComponent() = default;

		private:
			void SetDarkThemeColors();
			const char* _title;
			static inline int _componentsInit = 0;
	};
}

#endif // __AK_IMGUI_COMPONENT__
