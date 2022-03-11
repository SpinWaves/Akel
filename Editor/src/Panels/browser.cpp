// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 11/03/2022

#include <Panels/browser.h>

Browser::Browser(std::shared_ptr<Ak::ELTM> eltm) : Panel("__browser")
{
    _eltm = eltm;
}

void Browser::onUpdate(Ak::Maths::Vec2<int>& size)
{
	if(ImGui::Begin(_eltm->getLocalText("Browser.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
		ImGui::End();
    }
}
