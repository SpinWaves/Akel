// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/08/2022
// Updated : 04/06/2023

#ifndef __AK_IMGUI_UTILS__
#define __AK_IMGUI_UTILS__

#include <Akpch.h>
#include <Renderer/Images/texture.h>

namespace AkImGui
{
	AK_API void WebLink(const char* text, const char* url, ImVec2 pos);

	class AK_API ImImage
	{
		friend AK_API ImImage LoadImage(std::filesystem::path file);

		public:
			ImImage() = default;

			inline ImTextureID getImGuiID() noexcept { return (ImTextureID)_set; }
			void destroy();

			~ImImage() = default;

		private:
			Ak::Texture _texture;
			VkDescriptorSet _set = VK_NULL_HANDLE;
	};

	AK_API ImImage LoadImage(std::filesystem::path file);
	AK_API bool Spinner(const char* label, float radius, int thickness, const ImU32& color);

	AK_API bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
	AK_API bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
	AK_API bool InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
}

#endif // __AK_IMGUI_UTILS__
