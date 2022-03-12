// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 12/03/2022
// Updated : 12/03/2022

#include <Panels/scene.h>

Scene::Scene(std::shared_ptr<Ak::ELTM> eltm) : Panel("__scene")
{
    _eltm = eltm;
}

void Scene::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(_eltm->getLocalText("Scene.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
        ImGui::End();
    }
}
