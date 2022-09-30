// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 30/09/2022

#include <Panels/materials.h>
#include <Fonts/material_font.h>

Materials::Materials(std::shared_ptr<Ak::ELTM> eltm) : Panel("__materials"), _new_material(false)
{
    _eltm = std::move(eltm);
}

void Materials::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(std::string(AKS_ICON_MD_CATEGORY" " + _eltm->getText("Materials.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
		if(ImGui::BeginChild("Materialsyy", ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetWindowHeight() - 90.0f), true, ImGuiWindowFlags_HorizontalScrollbar))
		{
			if(_names.empty())
			{
				ImGui::Dummy(ImVec2(42.0f, (ImGui::GetWindowHeight() - 90.0f) / 2.0f));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
					ImGui::Indent(((ImGui::GetWindowWidth() - 15.0f) / 2.0f) - ImGui::CalcTextSize(_eltm->getText("Materials.no_materials").c_str()).x / 2.0f);
					ImGui::TextUnformatted(_eltm->getText("Materials.no_materials").c_str());
				ImGui::PopStyleColor();
			}

			ImGui::EndChild();
		}
		ImGui::Separator();
		if(ImGui::Button(std::string(_eltm->getText("Materials.add") + " "AKS_ICON_MD_ADD).c_str(), ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetFontSize() * 2.0f)))
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

			ImGui::Dummy(ImVec2(69.0f, ImGui::GetWindowHeight() - ImGui::GetFontSize() * 6.5f));
			ImGui::Separator();

			if(ImGui::Button(std::string(_eltm->getText("Materials.create") + " "AKS_ICON_MD_NOTE_ADD).c_str(), ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetFontSize() * 2.0f)) && std::strlen(name) != 0)
			{
				_names.emplace_back(name);
				std::memset(name, 0, 128);
				_new_material = false;
			}

			ImGui::End();
		}
	}
}
