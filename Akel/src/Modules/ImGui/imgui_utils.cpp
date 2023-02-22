// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/08/2022
// Updated : 22/02/2023

#include <Akpch.h>
#include <Core/log.h>
#include <Modules/ImGui/imgui_utils.h>

namespace AkImGui
{
	void openWebPage(const char* url)
	{
		#ifdef AK_PLATFORM_WINDOWS
			ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWDEFAULT);
		#else
			#ifdef AK_PLATFROM_OSX
				const char* open_executable = "open";
			#else
				const char* open_executable = "xdg-open";
			#endif
			char command[512] = { 0 };
			std::snprintf(command, 512, "%s \"%s\"", open_executable, url);
			std::system(command);
		#endif
	}

	void WebLink(const char* text, const char* url, ImVec2 pos)
	{
		ImGui::SetCursorPos(pos);
		ImGui::TextUnformatted(text);
		ImGui::SetCursorPos(pos);
		if(ImGui::InvisibleButton(text, ImGui::CalcTextSize(text)))
			openWebPage(url);
		if(ImGui::IsItemHovered())
		{
			ImGui::SetCursorPos(pos);
			ImDrawList* draw_list = ImGui::GetForegroundDrawList();
			ImVec2 text_size = ImGui::CalcTextSize(text);
			ImVec2 abs_pos = ImGui::GetCursorScreenPos();
			ImVec4* colors = ImGui::GetStyle().Colors;
			draw_list->AddLine(ImVec2(abs_pos.x, abs_pos.y + text_size.y), ImVec2(abs_pos.x + text_size.x, abs_pos.y + text_size.y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(colors[ImGuiCol_Text])));
		}
	}

	ImImage LoadImage(std::filesystem::path file)
	{
		ImImage image;

		if(!std::filesystem::exists(file))
			Ak::Core::log::report(FATAL_ERROR, "ImGui : failed to load image");
		image._texture = Ak::loadTextureFromFile(std::move(file));
		image._set = ImGui_ImplVulkan_AddTexture(image._texture.getSampler(), image._texture.getImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		return image;
	}

	void ImImage::destroy()
	{
		_texture.destroy();
	}
}
