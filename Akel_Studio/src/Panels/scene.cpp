// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 12/03/2022
// Updated : 24/08/2022

#include <Panels/scene.h>
#include <Fonts/material_font.h>

Scene::Scene(std::shared_ptr<Ak::ELTM> eltm) : Panel("__scene")
{
    _eltm = std::move(eltm);
}

void Scene::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(std::string(AKS_ICON_MD_SPORTS_ESPORTS" " + _eltm->getLocalText("Scene.name")).c_str(), nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground))
    {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

        if(ImGui::BeginMenuBar())
        {
            if(ImGui::BeginMenu(std::string(AKS_ICON_MD_ASPECT_RATIO" " + _eltm->getLocalText("Scene.aspect")).c_str()))
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
            if(ImGui::BeginMenu(std::string(AKS_ICON_MD_PANORAMA" " + _eltm->getLocalText("Scene.view")).c_str()))
            {
				ImGui::Checkbox(std::string(AKS_ICON_MD_GRID_4X4" " + _eltm->getLocalText("Scene.grid")).c_str(), &_grid);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        int aspect_width = 0;
        const int window_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
        const int window_height = size.Y - size.Y/4 - 25;
		float aspect = window_width / window_height;

        switch(_aspect_checked)
        {
            case 1 : aspect_width = (window_width - (window_height * 1.6)) / 2; aspect = 1.6f; break;
            case 2 : aspect_width = (window_width - (window_height * 1.78)) / 2; aspect = 16 / 9; break;
            case 3 : aspect_width = (window_width - (window_height * 1.3)) / 2; aspect = 4 / 3; break;
            case 4 : aspect_width = (window_width - (window_height * 1.5)) / 2; aspect = 1.5f; break;
            case 5 : aspect_width = (window_width - (window_height * 0.5625)) / 2; aspect = 9 / 16; break;

            default : break;
        }
        
		ImGuizmo::SetRect(ImGui::GetWindowPos().x + aspect_width, ImGui::GetWindowPos().y - 200, window_width - aspect_width, window_height + 400);
        
        ImGuizmo::SetDrawlist();

        Ak::Matrixes::perspective(90, aspect, 0.01, 1000);

		if(_grid)
			ImGuizmo::DrawGrid(glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::view)), glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::proj)), glm::value_ptr(glm::mat4(1.0f)), 1000.f);
		ImGuizmo::DrawCubes(glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::view)), glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::proj)), glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::model)), 1);

        draw_list->AddRectFilled(ImVec2((15 * size.X)/100, 0), ImVec2(aspect_width, size.Y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.180f, 0.180f, 0.180f, 1.000f))));
        draw_list->AddRectFilled(ImVec2(size.X - (19 * size.X)/100, 0), ImVec2(size.X - (19 * size.X)/100 - aspect_width, size.Y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.180f, 0.180f, 0.180f, 1.000f))));

        ImGui::End();
    }
}
