// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/07/2021
// Updated : 07/02/2023

#ifndef __AK_IMGUI_COMPONENT__
#define __AK_IMGUI_COMPONENT__

#include <Akpch.h>
#include <Core/Components/baseComponent.h>

namespace Ak
{
	class AK_API ImGuiComponent : public Component
	{
		friend class Application;

		public:
			ImGuiComponent(class RendererComponent* renderer);

			void onAttach() override;
			void onImGuiEvent(class Input& input) override;
			void onQuit() override;

			void addFontFromFile(const char* file, float size, bool def = false);
			void addFontFromRawTTF(uint32_t* data, size_t data_size, ImFontConfig conf, ImWchar* ranges, float size, bool def = false);
			void generateFonts();

			// Needs to be called before onAttach() to work
			// Calling it without parameter will reset to the default path
			inline void setSettingsFilePath(const char* path = "imgui.ini") noexcept { _settingsFilePath = path; }
			static inline bool getNumComp() noexcept { return _componentsInit; }

			virtual ~ImGuiComponent() = default;

		private:
			void SetDarkThemeColors();
			void renderFrame();
			std::string _settingsFilePath = "imgui.ini";
			class RendererComponent* _renderer = nullptr;
			static inline bool _componentsInit = false;
	};
}

#endif // __AK_IMGUI_COMPONENT__
