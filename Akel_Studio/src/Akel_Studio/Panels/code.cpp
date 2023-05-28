// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/05/2023
// Updated : 28/05/2023

#include <Panels/code.h>
#include <Fonts/material_font.h>

CodeEditor::CodeEditor(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__code_editor", project)
{
	_eltm = std::move(eltm);
}

void CodeEditor::onUpdate(Ak::Vec2i& size)
{
	if(ImGui::Begin(std::string(AKS_ICON_MD_CODE" " + _eltm->getText("Code.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		ImGui::End();
	}
}
