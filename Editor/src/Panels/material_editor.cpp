// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 11/03/2022

#include <Panels/material_editor.h>

MaterialEditor::MaterialEditor(std::shared_ptr<Ak::ELTM> eltm) : Panel("__entities")
{
    _eltm = eltm;
}

void MaterialEditor::onUpdate(Ak::Maths::Vec2<int>& size)
{
	if(ImGui::Begin(_eltm->getLocalText("MaterialEditor.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
		ImGui::End();
    }
}
