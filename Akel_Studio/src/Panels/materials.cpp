// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 09/07/2022

#include <Panels/materials.h>

Materials::Materials(std::shared_ptr<Ak::ELTM> eltm) : Panel("__materials")
{
    _eltm = std::move(eltm);
}

void Materials::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(_eltm->getLocalText("Materials.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
        ImGui::End();
    }
}
