// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/07/2021
// Updated : 16/08/2022

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

			void addFontFromFile(const char* file, float size, bool def = false);
			void addFontFromRawTTF(uint32_t* data, size_t data_size, ImFontConfig conf, ImWchar* ranges, float size, bool def = false);
			void generateFonts();

			// Needs to be called before onAttach() to work
			// Calling it without parameter will reset to the default path
			inline void setSettingsFilePath(const char* path = "imgui.ini") noexcept { _settingsFilePath = path; }
			static inline int getNumComp() noexcept { return _componentsInit; }

			virtual ~ImGuiComponent() = default;

		private:
			void SetDarkThemeColors();
			std::string _settingsFilePath = "imgui.ini";
			static inline int _componentsInit = 0;
	};
}

#endif // __AK_IMGUI_COMPONENT__
