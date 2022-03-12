// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#include <Panels/entities_manager.h>

EntitiesManager::EntitiesManager(std::shared_ptr<Ak::ELTM> eltm) : Panel("__entities_manager")
{
    _eltm = eltm;
}

void EntitiesManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = (15 * size.X)/100;
    _height = size.Y - (50 * size.Y)/100;
	if(ImGui::Begin(_eltm->getLocalText("EntitiesManager.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
		ImGui::SetWindowPos(ImVec2(0, _height));
		ImGui::SetWindowSize(ImVec2(_width, _height));

		ImGui::End();
    }
}
