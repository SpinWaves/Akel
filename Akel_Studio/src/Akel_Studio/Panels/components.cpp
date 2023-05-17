// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/11/2022
// Updated : 17/05/2023

#include "components.h"
#include <Fonts/material_font.h>

Components::Components(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__components", project)
{
	_eltm = std::move(eltm);
	_components[std::string(AKS_ICON_MD_VIDEO_LABEL" " + _eltm->getText("Components.window"))] = false;
	_components[std::string(AKS_ICON_MD_VIDEO_STABLE" " + _eltm->getText("Components.renderer"))] = false;
	_components[std::string(AKS_ICON_MD_WIDGETS" " + _eltm->getText("Components.imgui"))] = false;
	_components[std::string(AKS_ICON_MD_VIEW_IN_AR" " + _eltm->getText("Components.scenes"))] = false;
	_components[std::string(AKS_ICON_MD_VOLUME_UP" " + _eltm->getText("Components.audio"))] = false;
	_components[std::string(AKS_ICON_MD_PLAY_CIRCLE_FILLED" " + _eltm->getText("Components.animator"))] = false;
}

void Components::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = (15 * size.X) / 100;
	_height = size.Y - 25 - (50 * size.Y) / 100;
	if(ImGui::Begin(std::string(AKS_ICON_MD_LIST" " + _eltm->getText("Components.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		ImGui::SetWindowPos(ImVec2(0, 25));
		ImGui::SetWindowSize(ImVec2(_width, _height));

		if(ImGui::BeginChild("components", ImVec2(0, 0), true))
		{
			if(ImGui::BeginChild("components_names", ImVec2(ImGui::CalcTextSize(std::string(AKS_ICON_MD_VIEW_IN_AR" " + _eltm->getText("Components.scenes")).c_str()).x + 5, 0)))
			{
				for(auto it = _components.begin(); it != _components.end(); ++it)
				{
					ImGui::TextUnformatted(it->first.c_str());
					ImGui::Separator();
				}
				ImGui::EndChild();
			}
			ImGui::SameLine();
			if(ImGui::BeginChild("components_checkboxes"))
			{
				for(auto it = _components.begin(); it != _components.end(); ++it)
					ImGui::Checkbox(std::string("##" + it->first).c_str(), &it->second);
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}

		ImGui::End();
	}
}
