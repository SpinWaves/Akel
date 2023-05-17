// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 17/05/2023

#include <Panels/materials.h>
#include <Fonts/material_font.h>

Materials::Materials(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__materials", project), _new_material(false)
{
    _eltm = std::move(eltm);
}

void Materials::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(std::string(AKS_ICON_MD_CATEGORY" " + _eltm->getText("Materials.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
		ImVec2 child_size = ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetWindowHeight() - 90.0f);
		if(ImGui::BeginChild("Materials", child_size, true))
		{
			if(_names.empty())
			{
				ImGui::Dummy(ImVec2(42.0f, (ImGui::GetWindowHeight() - 90.0f) / 2.0f));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
					ImGui::Indent(((ImGui::GetWindowWidth() - 15.0f) / 2.0f) - ImGui::CalcTextSize(_eltm->getText("Materials.no_materials").c_str()).x / 2.0f);
					ImGui::TextUnformatted(_eltm->getText("Materials.no_materials").c_str());
				ImGui::PopStyleColor();
			}
			else
			{
				int i = 0;
				for(auto it = _names.begin(); it != _names.end(); it++)
				{
					if(ImGui::BeginChild(it->c_str(), ImVec2(child_size.x / 2.15f, child_size.y / 2.15f), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
					{
						ImGui::Dummy(ImVec2(10.0f, child_size.y / 2.15f - ImGui::GetTextLineHeight() * 2.0f));
						ImGui::Separator();
						
						ImGui::TextUnformatted(it->c_str());
						
						ImGui::SameLine(child_size.x / 2.15f - 32.5f);

						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
						if(ImGui::SmallButton(AKS_ICON_MD_MORE_VERT))
							ImGui::OpenPopup("material_toggle");
						ImGui::PopStyleVar();
						
						static bool rename = false;

						if(ImGui::BeginPopup("material_toggle"))
						{
							if(ImGui::MenuItem(_eltm->getText("Materials.delete").c_str()))
							{
								_names.erase(it);
								if(it == _names.end())
									it--;
							}
							if(ImGui::MenuItem(_eltm->getText("Materials.rename").c_str()))
								rename = true;
							ImGui::EndPopup();
						}

						if(rename && ImGui::Begin(std::string(AKS_ICON_MD_CATEGORY" " + _eltm->getText("Materials.rename")).c_str(), &rename, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
						{
							ImGui::SetWindowPos(ImVec2(size.X / 2.0f - 200.0f, size.Y / 2.0f - 60.0f));
							ImGui::SetWindowSize(ImVec2(400.0f, 120.0f));
							ImGui::SetWindowFocus();
							static char name[128] = { 0 };
							ImGui::TextUnformatted(_eltm->getText("Materials.mat_name").c_str());
							ImGui::SameLine();
							ImGui::InputText("##material_name", name, 128);
							ImGui::Separator();

							bool already_exists = std::find_if(_names.begin(), _names.end(), [&](std::string s) { return std::strcmp(s.c_str(), name) == 0; }) != _names.end();

							if(ImGui::Button(std::string(_eltm->getText("Materials.rename") + " " AKS_ICON_MD_NOTE_ADD).c_str(), ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetFontSize() * 2.0f)) && std::strlen(name) != 0 && !already_exists)
							{
								*it = name;
								std::memset(name, 0, 128);
								rename = false;
							}
							if(ImGui::IsItemHovered() && already_exists)
								ImGui::SetTooltip(_eltm->getText("Materials.already_created").c_str());

							ImGui::End();
						}
						
						ImGui::EndChild();
					}
					if(i % 2 == 0)
						ImGui::SameLine();
					i++;
				}
			}

			ImGui::EndChild();
		}
		ImGui::Separator();
		if(ImGui::Button(std::string(_eltm->getText("Materials.add") + " " AKS_ICON_MD_ADD).c_str(), ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetFontSize() * 2.0f)))
			_new_material = true;
        ImGui::End();
    }

	if(_new_material)
	{
		ImGui::SetNextWindowPos(ImVec2(size.X / 2.0f - 200.0f, size.Y / 2.0f - 200.0f));
		ImGui::SetNextWindowSize(ImVec2(400.0f, 400.0f));
		ImGui::SetNextWindowFocus();
		if(ImGui::Begin(std::string(AKS_ICON_MD_CATEGORY" " + _eltm->getText("Materials.add")).c_str(), &_new_material, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			static char name[128] = { 0 };
			ImGui::TextUnformatted(_eltm->getText("Materials.mat_name").c_str());
			ImGui::SameLine();
            ImGui::InputText("##material_name", name, 128);

			static char shader[512] = { 0 };
			ImGui::TextUnformatted(_eltm->getText("Materials.shader_bind").c_str());
			ImGui::SameLine();
            ImGui::InputText("##shader_bind", shader, 512);

			ImGui::Dummy(ImVec2(69.0f, ImGui::GetWindowHeight() - ImGui::GetFontSize() * 8.5f));
			ImGui::Separator();

			bool already_exists = std::find_if(_names.begin(), _names.end(), [&](std::string s) { return std::strcmp(s.c_str(), name) == 0; }) != _names.end();

			if(ImGui::Button(std::string(_eltm->getText("Materials.create") + " " AKS_ICON_MD_NOTE_ADD).c_str(), ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetFontSize() * 2.0f)) && std::strlen(name) != 0 && !already_exists)
			{
				_names.emplace_back(name);
				std::memset(name, 0, 128);
				_new_material = false;
			}
			if(ImGui::IsItemHovered() && already_exists)
				ImGui::SetTooltip(_eltm->getText("Materials.already_created").c_str());

			ImGui::End();
		}
	}
}
