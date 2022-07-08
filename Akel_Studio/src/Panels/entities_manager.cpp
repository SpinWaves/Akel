// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 08/07/2022

#include <Panels/entities_manager.h>

EntitiesManager::EntitiesManager(std::shared_ptr<Ak::ELTM> eltm) : Panel("__entities_manager")
{
    _eltm = eltm;
}

void EntitiesManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = (15 * size.X)/100;
    _height = size.Y - (50 * size.Y)/100;
	if(ImGui::Begin(_eltm->getLocalText("EntitiesManager.name").c_str(), nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
		ImGui::SetWindowPos(ImVec2(0, _height));
		ImGui::SetWindowSize(ImVec2(_width, _height));

		render_transform();

		ImGui::End();
    }
}

void EntitiesManager::render_transform()
{
	if(ImGui::CollapsingHeader(_eltm->getLocalText("EntitiesManager.transform").c_str(), ImGuiTreeNodeFlags_SpanFullWidth))
    {
		if(ImGui::BeginChild("entity_manager_texts", ImVec2(ImGui::CalcTextSize(_eltm->getLocalText("EntitiesManager.pos").c_str()).x + 5, 90), false))
		{
			ImGui::Text(_eltm->getLocalText("EntitiesManager.pos").c_str());
			ImGui::Separator();
			ImGui::Text(_eltm->getLocalText("EntitiesManager.rot").c_str());
			ImGui::Separator();
			ImGui::Text(_eltm->getLocalText("EntitiesManager.sca").c_str());

			ImGui::EndChild();
		}

        ImGui::SameLine(0);

		if(ImGui::BeginChild("entity_manager_drags", ImVec2(150, 90), false))
		{
			static float v[3];
			ImGui::SetNextItemWidth(150);
			ImGui::DragFloat3("0", v);

			static float v1[3];
			ImGui::SetNextItemWidth(150);
			ImGui::DragFloat3("1", v1);

			static float v2[3];
			ImGui::SetNextItemWidth(150);
			ImGui::DragFloat3("2", v2);

			ImGui::EndChild();
		}

		ImGui::Separator();
    }
}
