// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/07/2021
// Updated : 05/07/2022

#ifndef __AK_IMGUI_COMPONENT__
#define __AK_IMGUI_COMPONENT__

#include <Akpch.h>
#include <Platform/input.h>
#include <Core/core.h>

namespace Ak
{
	class ImGuiComponent : public Component
	{
		public:
			ImGuiComponent();

			void onAttach() override;
			void onImGuiEvent(Input& input) override;
			void onQuit() override;

			// Needs to be called before onAttach() to work
			// Calling it without parameter will reset to the default path
			inline void setSettingsFilePath(const char* path = nullptr) noexcept { _settingsFilePath = path; }
			static inline int getNumComp() noexcept { return _componentsInit; }

			virtual ~ImGuiComponent() = default;

		private:
			void SetDarkThemeColors();
			const char* _settingsFilePath = nullptr;
			static inline int _componentsInit = 0;
	};
}

#endif // __AK_IMGUI_COMPONENT__
