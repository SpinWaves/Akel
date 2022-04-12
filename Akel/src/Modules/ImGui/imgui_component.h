// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/07/2021
// Updated : 12/04/2022

#ifndef __AK_IMGUI_COMPONENT__
#define __AK_IMGUI_COMPONENT__

#include <Akpch.h>
#include <Platform/window.h>

namespace Ak
{
	class ImGuiComponent : public Component
	{
		friend class Application;
		public:
			ImGuiComponent(WindowComponent* window);

			void onAttach() override;
			void onImGuiEvent(Input& input) override;
			void onQuit() override;

			void begin(); // Do not use, the application will call it for you
			void end(); // Do not use, the application will call it for you

			// Needs to be called before onAttach() to work
			// Calling it without parameter will reset to the default path
			inline void setSettingsFilePath(const char* path = nullptr) noexcept { _settingsFilePath = path; }
			static inline int getNumComp() noexcept { return _componentsInit; }

			virtual ~ImGuiComponent() = default;

		private:
			ImGuiComponent();
			
			void SetDarkThemeColors();
			const char* _settingsFilePath = nullptr;
			static inline int _componentsInit = 0;
			WindowComponent* _win = nullptr;
	};
}

#endif // __AK_IMGUI_COMPONENT__
