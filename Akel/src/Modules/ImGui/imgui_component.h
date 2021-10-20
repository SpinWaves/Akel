// This file is a part of Akel
// CREATED : 03/07/2021
// UPDATED : 16/10/2021

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

			void begin(); // Do not use, the application will call it for you
			void end(); // Do not use, the application will call it for you

			// Needs to be called before onAttach() to work
			void setSettingsFilePath(const char* path = nullptr) // Calling it without parameter will reset to the default path
			{
				_settingsFilePath = path;
				std::cout << "oui " << _settingsFilePath << std::endl;
			}

			static int getNumComp() { return _componentsInit; }

			virtual ~ImGuiComponent() = default;

		private:
			void SetDarkThemeColors();
			const char* _title = nullptr;
			const char* _settingsFilePath = nullptr;
			static inline int _componentsInit = 0;
	};
}

#endif // __AK_IMGUI_COMPONENT__
