// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/07/2021
// Updated : 23/02/2023

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
			ImGuiComponent(class RendererComponent* renderer, std::string file_path = "default", bool generate_font = true);

			void onAttach() override;
			void onImGuiEvent(class Input& input) override;
			void onQuit() override;

			void addFontFromFile(const char* file, float size, bool def = false);
			void addFontFromRawTTF(uint32_t* data, size_t data_size, ImFontConfig conf, ImWchar* ranges, float size, bool def = false);
			void generateFonts();

			static inline bool getNumComp() noexcept { return _componentsInit; }

			virtual ~ImGuiComponent() = default;

		private:
			void SetDarkThemeColors();
			void begin();
			void renderFrame();

			std::string _settingsFilePath;
			class RendererComponent* _renderer = nullptr;
			static inline bool _componentsInit = false;
			bool _generate_font_on_attach = true;
	};
}

#endif // __AK_IMGUI_COMPONENT__
