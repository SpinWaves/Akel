// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 12/03/2022
// Updated : 05/07/2022

#include <Panels/scene.h>

Scene::Scene(std::shared_ptr<Ak::ELTM> eltm) : Panel("__scene")
{
    _eltm = eltm;
}

void Scene::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(_eltm->getLocalText("Scene.name").c_str(), nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground))
    {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

        if(ImGui::BeginMenuBar())
        {
            if(ImGui::BeginMenu(_eltm->getLocalText("Scene.aspect").c_str()))
            {
                if(ImGui::MenuItem(_eltm->getLocalText("Scene.free_aspect").c_str(), NULL, _aspect_checked == 0))
                    _aspect_checked = 0;
                if(ImGui::MenuItem("16:10", NULL, _aspect_checked == 1))
                    _aspect_checked = 1;
                if(ImGui::MenuItem("16:9", NULL, _aspect_checked == 2))
                    _aspect_checked = 2;
                if(ImGui::MenuItem("4:3", NULL, _aspect_checked == 3))
                    _aspect_checked = 3;
                if(ImGui::MenuItem("3:2", NULL, _aspect_checked == 4))
                    _aspect_checked = 4;
                if(ImGui::MenuItem("9:16", NULL, _aspect_checked == 5))
                    _aspect_checked = 5;

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        int aspect_width = 0;

        switch(_aspect_checked)
        {
            case 1 : aspect_width = 100; break;
            case 2 : aspect_width = 200; break;
            case 3 : aspect_width = 300; break;
            case 4 : aspect_width = 400; break;
            case 5 : aspect_width = 500; break;

            default : break;
        }
        
        draw_list->AddRectFilled(ImVec2(0, 0), ImVec2((15 * size.X)/100 + aspect_width, size.Y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.180f, 0.180f, 0.180f, 1.000f))));
        draw_list->AddRectFilled(ImVec2(size.X, 0), ImVec2(size.X - (19 * size.X)/100 - aspect_width, size.Y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.180f, 0.180f, 0.180f, 1.000f))));
        
        ImGui::End();
    }
}
