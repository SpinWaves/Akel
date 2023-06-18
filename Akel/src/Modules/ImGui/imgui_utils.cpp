// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/08/2022
// Updated : 18/06/2023

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

	ImImage LoadImageEmpy(uint32_t width, uint32_t height)
	{
		ImImage image;

		std::shared_ptr<Ak::Texture> texture = std::make_shared<Ak::Texture>();
		texture->create(nullptr, width, height, VK_FORMAT_R8G8B8A8_UNORM);
		image._texture = Ak::TextureLibrary::get().addTextureToLibrary(texture);
		image._set = ImGui_ImplVulkan_AddTexture(texture->getSampler(), texture->getImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		return image;
	}

	ImImage LoadImage(std::filesystem::path file)
	{
		ImImage image;

		if(!std::filesystem::exists(file))
			Ak::Core::log::report(FATAL_ERROR, "ImGui : failed to load image");
		image._texture = Ak::TextureLibrary::get().addTextureToLibrary(std::move(file));
		std::shared_ptr<Ak::Texture> texture = Ak::TextureLibrary::get().getTexture(image._texture);
		image._set = ImGui_ImplVulkan_AddTexture(texture->getSampler(), texture->getImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		return image;
	}

	void ImImage::destroy()
	{
		ImGui_ImplVulkan_RemoveTexture(_set);
	}

	struct InputTextCallback_UserData
	{
		std::string* Str;
		ImGuiInputTextCallback ChainCallback;
		void* ChainCallbackUserData;
	};

	static int InputTextCallback(ImGuiInputTextCallbackData* data)
	{
		InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
		if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
		{
			std::string* str = user_data->Str;
			IM_ASSERT(data->Buf == str->c_str());
			str->resize(data->BufTextLen);
			data->Buf = (char*)str->c_str();
		}
		else if (user_data->ChainCallback)
		{
			data->UserData = user_data->ChainCallbackUserData;
			return user_data->ChainCallback(data);
		}
		return 0;
	}

	bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
	{
		IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
		flags |= ImGuiInputTextFlags_CallbackResize;

		InputTextCallback_UserData cb_user_data;
		cb_user_data.Str = str;
		cb_user_data.ChainCallback = callback;
		cb_user_data.ChainCallbackUserData = user_data;
		return ImGui::InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
	}

	bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
	{
		IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
		flags |= ImGuiInputTextFlags_CallbackResize;

		InputTextCallback_UserData cb_user_data;
		cb_user_data.Str = str;
		cb_user_data.ChainCallback = callback;
		cb_user_data.ChainCallbackUserData = user_data;
		return ImGui::InputTextMultiline(label, (char*)str->c_str(), str->capacity() + 1, size, flags, InputTextCallback, &cb_user_data);
	}

	bool InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
	{
		IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
		flags |= ImGuiInputTextFlags_CallbackResize;

		InputTextCallback_UserData cb_user_data;
		cb_user_data.Str = str;
		cb_user_data.ChainCallback = callback;
		cb_user_data.ChainCallbackUserData = user_data;
		return ImGui::InputTextWithHint(label, hint, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
	}

	bool Spinner(const char* label, float radius, int thickness, const ImU32& color)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if(window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ImGui::ItemSize(bb, style.FramePadding.y);
		if(!ImGui::ItemAdd(bb, id))
			return false;

		window->DrawList->PathClear();

		int num_segments = 30;
		int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

		const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
		const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

		for(int i = 0; i < num_segments; i++)
		{
			const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
			window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
							centre.y + ImSin(a + g.Time * 8) * radius));
		}
		window->DrawList->PathStroke(color, false, thickness);
	}
}
