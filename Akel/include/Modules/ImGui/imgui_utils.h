// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/08/2022
// Updated : 05/03/2023

#ifndef __AK_IMGUI_UTILS__
#define __AK_IMGUI_UTILS__

#include <Akpch.h>
#include <Renderer/Images/texture.h>

namespace AkImGui
{
	void WebLink(const char* text, const char* url, ImVec2 pos);

	class ImImage
	{
		friend ImImage LoadImage(std::filesystem::path file);

		public:
			ImImage() = default;

			inline ImTextureID getImGuiID() noexcept { return (ImTextureID)_set; }
			void destroy();

			~ImImage() = default;

		private:
			Ak::Texture _texture;
			VkDescriptorSet _set = VK_NULL_HANDLE;
	};

	ImImage LoadImage(std::filesystem::path file);
}

#endif // __AK_IMGUI_UTILS__
