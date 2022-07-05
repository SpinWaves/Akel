// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 12/03/2022
// Updated : 06/07/2022

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
        const int window_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
        const int window_height = size.Y - size.Y/4 - 25;

        switch(_aspect_checked)
        {
            case 1 : aspect_width = (window_width - (window_height * 1.6)) / 2; break;
            case 2 : aspect_width = (window_width - (window_height * 1.78)) / 2; break;
            case 3 : aspect_width = (window_width - (window_height * 1.3)) / 2; break;
            case 4 : aspect_width = (window_width - (window_height * 1.5)) / 2; break;
            case 5 : aspect_width = (window_width - (window_height * 0.5625)) / 2; break;

            default : break;
        }
        
        draw_list->AddRectFilled(ImVec2(0, 0), ImVec2((15 * size.X)/100 + aspect_width, size.Y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.180f, 0.180f, 0.180f, 1.000f))));
        draw_list->AddRectFilled(ImVec2(size.X, 0), ImVec2(size.X - (19 * size.X)/100 - aspect_width, size.Y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.180f, 0.180f, 0.180f, 1.000f))));
        
        ImGuizmo::Enable(true);
        ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, size.X, size.Y);

        Ak::Matrixes::perspective(90, (float)(size.X / size.Y), 0.01, 100);
    	Ak::Matrixes::lookAt(0, 0, 0, 1, 1, -1, 0, 0, 1);

        ImGuizmo::DrawGrid(glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::view)), glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::proj)), glm::value_ptr(glm::mat4(1.0f)), 100.f);

        ImGui::End();
        ImGuizmo::Enable(false);
    }
}
