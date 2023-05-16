// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/11/2022
// Updated : 16/05/2023

#include "components.h"
#include <Fonts/material_font.h>

Components::Components(std::shared_ptr<Ak::ELTM> eltm) : Panel("__components")
{
	_eltm = std::move(eltm);
}

void Components::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = (15 * size.X) / 100;
    _height = size.Y - 25 - (50 * size.Y) / 100;
	if(ImGui::Begin(std::string(AKS_ICON_MD_LIST" " + _eltm->getText("Components.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
		ImGui::SetWindowPos(ImVec2(0, 25));
		ImGui::SetWindowSize(ImVec2(_width, _height));

		ImGui::End();
    }
}
