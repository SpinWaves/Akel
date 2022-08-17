// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/08/2022
// Updated : 17/08/2022

#include <Akpch.h>
#include <Core/profile.h>

namespace AkImGui
{
	void openWebPage(const char* url)
	{
		#ifdef AK_PLATFORM_WINDOWS
			::ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWDEFAULT);
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
}
