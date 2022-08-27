// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 27/08/2022

#include <Panels/entities_manager.h>
#include <Fonts/material_font.h>

EntitiesManager::EntitiesManager(std::shared_ptr<Ak::ELTM> eltm) : Panel("__entities_manager")
{
    _eltm = std::move(eltm);
	Ak::Matrixes::matrix_mode(Ak::matrix::model);
	Ak::Matrixes::load_identity();
}

void EntitiesManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = (15 * size.X)/100;
    _height = size.Y - (50 * size.Y)/100;
	if(ImGui::Begin(std::string(AKS_ICON_MD_VIEW_IN_AR" " + _eltm->getText("EntitiesManager.name")).c_str(), nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
		ImGui::SetWindowPos(ImVec2(0, _height));
		ImGui::SetWindowSize(ImVec2(_width, _height));

		render_transform();

		ImGui::End();
    }
}

void EntitiesManager::render_transform()
{
	if(ImGui::CollapsingHeader(std::string(AKS_ICON_MD_360" " + _eltm->getText("EntitiesManager.transform")).c_str(), ImGuiTreeNodeFlags_SpanFullWidth))
    {
		if(ImGui::BeginChild("entity_manager_texts", ImVec2(ImGui::CalcTextSize(std::string(AKS_ICON_MD_NEAR_ME" " + _eltm->getText("EntitiesManager.pos")).c_str()).x + 5, 90), false))
		{
			ImGui::Text(std::string(AKS_ICON_MD_NEAR_ME" " + _eltm->getText("EntitiesManager.pos")).c_str());
			ImGui::Separator();
			ImGui::Text(std::string(AKS_ICON_MD_CROP_ROTATE" " + _eltm->getText("EntitiesManager.rot")).c_str());
			ImGui::Separator();
			ImGui::Text(std::string(AKS_ICON_MD_CROP" " + _eltm->getText("EntitiesManager.sca")).c_str());

			ImGui::EndChild();
		}

        ImGui::SameLine(0);

		if(ImGui::BeginChild("entity_manager_drags", ImVec2(150, 90), false))
		{
			Ak::Matrixes::matrix_mode(Ak::matrix::model);
			Ak::Matrixes::load_identity();

			static float v[3] = { 0.0f, 0.0f, 0.0f };
			ImGui::SetNextItemWidth(150);
			ImGui::DragFloat3("0", v);

			Ak::Matrixes::translate3D(v[0], v[1], v[2]);

			static float v1[3] = { 0.0f, 0.0f, 0.0f };
			ImGui::SetNextItemWidth(150);
			ImGui::DragFloat3("1", v1);

			static float v2[3] = { 1.0f, 1.0f, 1.0f };
			ImGui::SetNextItemWidth(150);
			ImGui::DragFloat3("2", v2);

			Ak::Matrixes::scale3D(v2[0], v2[1], v2[2]);

			ImGui::EndChild();
		}

		ImGui::Separator();
    }
}
