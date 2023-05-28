// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/11/2022
// Updated : 26/05/2023

#include "components.h"
#include <Fonts/material_font.h>

Components::Components(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__components", project)
{
	_eltm = std::move(eltm);
	if(!_project.keyExists("__window_component"))
		_project.archive()["__window_component"] = false;
	if(!_project.keyExists("__renderer_component"))
		_project.archive()["__renderer_component"] = false;
	if(!_project.keyExists("__imgui_component"))
		_project.archive()["__imgui_component"] = false;
	if(!_project.keyExists("__scenes_manager_component"))
		_project.archive()["__scenes_manager_component"] = false;
	if(!_project.keyExists("__audio_component"))
		_project.archive()["__audio_component"] = false;
	if(!_project.keyExists("__animator_component"))
		_project.archive()["__animator_component"] = false;
	_components[std::string(AKS_ICON_MD_VIDEO_LABEL" " + _eltm->getText("Components.window"))] = _project.archive()["__window_component"];
	_components[std::string(AKS_ICON_MD_VIDEO_STABLE" " + _eltm->getText("Components.renderer"))] = _project.archive()["__renderer_component"];
	_components[std::string(AKS_ICON_MD_WIDGETS" " + _eltm->getText("Components.imgui"))] = _project.archive()["__imgui_component"];
	_components[std::string(AKS_ICON_MD_VIEW_IN_AR" " + _eltm->getText("Components.scenes"))] = _project.archive()["__scenes_manager_component"];
	_components[std::string(AKS_ICON_MD_VOLUME_UP" " + _eltm->getText("Components.audio"))] = _project.archive()["__audio_component"];
	_components[std::string(AKS_ICON_MD_PLAY_CIRCLE_FILLED" " + _eltm->getText("Components.animator"))] = _project.archive()["__animator_component"];
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
			static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg;
			if(ImGui::BeginTable("components_table", 2, flags))
			{
				ImGui::TableSetupColumn("comp_names", ImGuiTableColumnFlags_NoHeaderLabel | ImGuiTableColumnFlags_WidthFixed,
										ImGui::CalcTextSize(std::string(AKS_ICON_MD_VIEW_IN_AR" " + _eltm->getText("Components.scenes")).c_str()).x + 10);
				ImGui::TableSetupColumn("comp_check", ImGuiTableColumnFlags_NoHeaderLabel | ImGuiTableColumnFlags_WidthFixed);

				for(auto it = _components.begin(); it != _components.end(); ++it)
				{
                	ImGui::TableNextRow();
                	ImGui::TableNextColumn();
					ImGui::TextUnformatted(it->first.c_str());
                	ImGui::TableNextColumn();
					ImGui::Checkbox(std::string("##" + it->first).c_str(), &it->second);
				}

				ImGui::EndTable();
			}
			ImGui::EndChild();
		}

		ImGui::End();
	}
}

void Components::writeComponents()
{	
	_project.archive()["__window_component"] = _components[std::string(AKS_ICON_MD_VIDEO_LABEL" " + _eltm->getText("Components.window"))];
	_project.archive()["__renderer_component"] = _components[std::string(AKS_ICON_MD_VIDEO_STABLE" " + _eltm->getText("Components.renderer"))];
	_project.archive()["__imgui_component"] = _components[std::string(AKS_ICON_MD_WIDGETS" " + _eltm->getText("Components.imgui"))];
	_project.archive()["__scenes_manager_component"] = _components[std::string(AKS_ICON_MD_VIEW_IN_AR" " + _eltm->getText("Components.scenes"))];
	_project.archive()["__audio_component"] = _components[std::string(AKS_ICON_MD_VOLUME_UP" " + _eltm->getText("Components.audio"))];
	_project.archive()["__animator_component"] = _components[std::string(AKS_ICON_MD_PLAY_CIRCLE_FILLED" " + _eltm->getText("Components.animator"))];
}

void Components::onQuit()
{
	writeComponents();
}
