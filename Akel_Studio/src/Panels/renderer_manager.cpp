// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 13/03/2022

#include <Panels/renderer_manager.h>

RendererManager::RendererManager(std::shared_ptr<Ak::ELTM> eltm) : Panel("__renderer_manager")
{
    _eltm = eltm;
    selected = _eltm->getLocalText("RendererManager.cull_none");
}

void RendererManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(_eltm->getLocalText("RendererManager.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
        render_sets();

        ImGui::End();
    }
}

void RendererManager::render_sets()
{
    if(ImGui::TreeNodeEx(_eltm->getLocalText("RendererManager.render_sets").c_str(), ImGuiTreeNodeFlags_Framed))
    {
        ImGui::Text(_eltm->getLocalText("RendererManager.culling").c_str());
        ImGui::SameLine();
        if(ImGui::BeginCombo("##combo", selected.c_str()))
        {
            static int item_current_idx = 0;
            if(ImGui::Selectable(_eltm->getLocalText("RendererManager.cull_none").c_str(), item_current_idx == 0))
            {
                item_current_idx = 0;
                selected = _eltm->getLocalText("RendererManager.cull_none");
            }
            if(ImGui::Selectable(_eltm->getLocalText("RendererManager.cull_front").c_str(), item_current_idx == 1))
            {
                item_current_idx = 1;
                selected = _eltm->getLocalText("RendererManager.cull_front");
            }
            if(ImGui::Selectable(_eltm->getLocalText("RendererManager.cull_back").c_str(), item_current_idx == 2))
            {
                item_current_idx = 2;
                selected = _eltm->getLocalText("RendererManager.cull_back");
            }
            if(ImGui::Selectable(_eltm->getLocalText("RendererManager.cull_front_and_back").c_str(), item_current_idx == 3))
            {
                item_current_idx = 3;
                selected = _eltm->getLocalText("RendererManager.cull_front_and_back");
            }
            ImGui::EndCombo();
        }
        
        static ImVec4 color = ImVec4(44.0f / 255.0f, 44.0f / 255.0f, 44.0f / 255.0f, 255.0f / 255.0f);
        ImGui::ColorEdit4("##picker", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        ImGui::SameLine();
        ImGui::Text(_eltm->getLocalText("RendererManager.bg_color").c_str());

        ImGui::Button(_eltm->getLocalText("RendererManager.reload").c_str());

        ImGui::Checkbox("Vsync", &_vsync);
        
        ImGui::TreePop();
    }
}
