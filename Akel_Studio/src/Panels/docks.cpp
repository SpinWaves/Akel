// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 17/08/2022

#include <Panels/docks.h>
#include <Fonts/material_font.h>

bool reload_docks = true;

Docks::Docks(std::shared_ptr<Ak::ELTM> eltm) : Panel("__docks")
{
    _eltm = std::move(eltm);
;
}

void Docks::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
	_height = size.Y / 4;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if(ImGui::Begin("ConsoleDockSpace", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
    {
		ImGui::SetWindowPos(ImVec2((15 * size.X)/100, size.Y - _height));
		ImGui::SetWindowSize(ImVec2(_width, _height));

        ImGuiID dockspace_id = ImGui::GetID("MyConsoleDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton);

        static int first_times_console = 0;
        if(reload_docks)
            first_times_console = 0;
        if(first_times_console < 2)
        {
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoWindowMenuButton);

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_TERMINAL" " + _eltm->getLocalText("Console.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_FOLDER_OPEN" " + _eltm->getLocalText("Browser.name")).data(), dockspace_id);
            ImGui::DockBuilderFinish(dockspace_id);

            first_times_console++;
        }

		ImGui::End();
    }

	_width = (19 * size.X)/100;
    _height = size.Y - 25 - (50 * size.Y)/100;

	if(ImGui::Begin("RendererDockSpace", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
    {
		ImGui::SetWindowPos(ImVec2(size.X - _width, 25));
		ImGui::SetWindowSize(ImVec2(_width, _height));

        ImGuiID dockspace_id = ImGui::GetID("MyRendererDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton);

        static int first_times_render = 0;
        if(reload_docks)
            first_times_render = 0;
        if(first_times_render < 2)
        {
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoWindowMenuButton);

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_VOLUME_UP" " + _eltm->getLocalText("AudioManager.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_TV" " + _eltm->getLocalText("RendererManager.name")).data(), dockspace_id);
            ImGui::DockBuilderFinish(dockspace_id);

            first_times_render++;
        }

		ImGui::End();
    }

	_width = (19 * size.X)/100;
    _height = size.Y - (50 * size.Y)/100;

	if(ImGui::Begin("MaterialsDockSpace", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
    {
		ImGui::SetWindowPos(ImVec2(size.X - _width, _height));
		ImGui::SetWindowSize(ImVec2(_width, _height));

        ImGuiID dockspace_id = ImGui::GetID("MyMaterialsDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton);

        static int first_times_materials = 0;
        if(reload_docks)
            first_times_materials = 0;
        if(first_times_materials < 2)
        {
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoWindowMenuButton);

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_DRAW" " + _eltm->getLocalText("MaterialEditor.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_CATEGORY" " + _eltm->getLocalText("Materials.name")).data(), dockspace_id);
            ImGui::DockBuilderFinish(dockspace_id);

            first_times_materials++;
        }

		ImGui::End();
    }

	_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
    _height = size.Y - size.Y/4 - 25;

	if(ImGui::Begin("SceneDockSpace", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground))
    {
		ImGui::SetWindowPos(ImVec2((15 * size.X)/100 - 1, 25 - 1));
		ImGui::SetWindowSize(ImVec2(_width + 2, _height + 2));

        ImGuiID dockspace_id = ImGui::GetID("MySceneDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_NoWindowMenuButton);

        static int first_times_scene = 0;
        if(reload_docks)
            first_times_scene = 0;
        if(first_times_scene < 2)
        {
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoWindowMenuButton);

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_TYPE_SPECIMEN" " + _eltm->getLocalText("ELTM_Editor.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_SPORTS_ESPORTS" " + _eltm->getLocalText("Scene.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_SETTINGS" " + _eltm->getLocalText("MainMenuBar.options")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_INFO" " + _eltm->getLocalText("MainMenuBar.about")).data(), dockspace_id);

            ImGui::DockBuilderFinish(dockspace_id);

            first_times_scene++;
        }

		ImGui::End();
    }

    ImGui::PopStyleVar();

    reload_docks = false;
}
