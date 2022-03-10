// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#include <Panels/browser.h>

Browser::Browser(std::shared_ptr<Ak::ELTM> eltm) : Panel("__browser")
{
    _eltm = eltm;
}

void Browser::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
	_height = size.Y / 4;
	if(ImGui::Begin(_eltm->getLocalText("Browser.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
		ImGui::SetWindowPos(ImVec2((15 * size.X)/100, size.Y - _height));
		ImGui::SetWindowSize(ImVec2(_width, _height));

		ImGui::End();
    }
}
