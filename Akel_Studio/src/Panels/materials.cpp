// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 29/09/2022

#include <Panels/materials.h>
#include <Fonts/material_font.h>

Materials::Materials(std::shared_ptr<Ak::ELTM> eltm) : Panel("__materials")
{
    _eltm = std::move(eltm);
}

void Materials::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(std::string(AKS_ICON_MD_CATEGORY" " + _eltm->getText("Materials.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
		if(ImGui::BeginChild("Materials", ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetWindowHeight() - 90.0f), true, ImGuiWindowFlags_HorizontalScrollbar))
		{
			ImGui::Dummy(ImVec2(42.0f, (ImGui::GetWindowHeight() - 90.0f) / 2.0f));
			
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
				ImGui::Indent(((ImGui::GetWindowWidth() - 15.0f) / 2.0f) - ImGui::CalcTextSize(_eltm->getText("Materials.no_materials").c_str()).x / 2.0f);
				ImGui::TextUnformatted(_eltm->getText("Materials.no_materials").c_str());
			ImGui::PopStyleColor();

			ImGui::EndChild();
		}
		ImGui::Separator();
		if(ImGui::Button(std::string(_eltm->getText("Materials.add") + " "AKS_ICON_MD_ADD).c_str(), ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetFontSize() * 2.0f)))
		{
		}
        ImGui::End();
    }
}
