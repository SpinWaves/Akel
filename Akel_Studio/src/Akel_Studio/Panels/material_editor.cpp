// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 17/05/2023

#include <Panels/material_editor.h>
#include <Fonts/material_font.h>

MaterialEditor::MaterialEditor(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project, const std::vector<std::string>& names) : Panel("__entities", project), _names(names)
{
    _eltm = std::move(eltm);
}

void MaterialEditor::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(std::string(AKS_ICON_MD_DRAW" " + _eltm->getText("MaterialEditor.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
		if(ImGui::TreeNodeEx(std::string(AKS_ICON_MD_QUERY_STATS" " + _eltm->getText("MaterialEditor.albedo")).c_str(), ImGuiTreeNodeFlags_Framed))
		{
			
			ImGui::TreePop();
		}
		if(ImGui::TreeNodeEx(std::string(AKS_ICON_MD_QUERY_STATS" " + _eltm->getText("MaterialEditor.metalness")).c_str(), ImGuiTreeNodeFlags_Framed))
		{
			static float metal = 0.0f;
			ImGui::SliderFloat("##slider_metlaness", &metal, 0.0f, 1.0f, "%.3f");
			ImGui::TreePop();
		}
		if(ImGui::TreeNodeEx(std::string(AKS_ICON_MD_QUERY_STATS" " + _eltm->getText("MaterialEditor.roughness")).c_str(), ImGuiTreeNodeFlags_Framed))
		{
			static float rough = 0.0f;
			ImGui::SliderFloat("##slider_roughness", &rough, 0.0f, 1.0f, "%.3f");
			ImGui::TreePop();
		}
		if(ImGui::TreeNodeEx(std::string(AKS_ICON_MD_QUERY_STATS" " + _eltm->getText("MaterialEditor.normals")).c_str(), ImGuiTreeNodeFlags_Framed))
		{
			static bool use = false;
			ImGui::Checkbox(_eltm->getText("MaterialEditor.use").c_str(), &use);
			ImGui::TreePop();
		}
        ImGui::End();
    }
}
