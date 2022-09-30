// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 30/09/2022

#include <Panels/material_editor.h>
#include <Fonts/material_font.h>

MaterialEditor::MaterialEditor(std::shared_ptr<Ak::ELTM> eltm, const std::vector<std::string>& names) : Panel("__entities"), _names(names)
{
    _eltm = std::move(eltm);
}

void MaterialEditor::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(std::string(AKS_ICON_MD_DRAW" " + _eltm->getText("MaterialEditor.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
        ImGui::End();
    }
}
