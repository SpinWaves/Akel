// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 28/05/2023

#include <Panels/docks.h>
#include <Fonts/material_font.h>

bool reload_docks = true;

Docks::Docks(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__docks", project)
{
    _eltm = std::move(eltm);
}

void Docks::onUpdate(Ak::Maths::Vec2<int>& size)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	_width = (15 * size.X)/100;
    _height = size.Y - 22 - (50 * size.Y)/100;

	if(ImGui::Begin("ComponentsDockSpace", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
    {
		ImGui::SetWindowPos(ImVec2(0, 22));
		ImGui::SetWindowSize(ImVec2(_width, _height));

        ImGuiID dockspace_id = ImGui::GetID("MyComponentsDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton);

        static int first_times_components = 0;
        if(reload_docks)
            first_times_components = 0;
        if(first_times_components < 2)
        {
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoWindowMenuButton);

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_LIST" " + _eltm->getText("Components.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_VIEW_IN_AR" " + _eltm->getText("Entities.name")).data(), dockspace_id);
            ImGui::DockBuilderFinish(dockspace_id);

            first_times_components++;
        }

		ImGui::End();
    }

	_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
	_height = size.Y / 4;

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

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_TERMINAL" " + _eltm->getText("Console.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_FOLDER_OPEN" " + _eltm->getText("Browser.name")).data(), dockspace_id);
            ImGui::DockBuilderFinish(dockspace_id);

            first_times_console++;
        }

		ImGui::End();
    }

	_width = (19 * size.X)/100;
    _height = size.Y - 22 - (50 * size.Y)/100;

	if(ImGui::Begin("RendererDockSpace", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
    {
		ImGui::SetWindowPos(ImVec2(size.X - _width, 22));
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

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_VOLUME_UP" " + _eltm->getText("AudioManager.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_TV" " + _eltm->getText("RendererManager.name")).data(), dockspace_id);
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

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_DRAW" " + _eltm->getText("MaterialEditor.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_CATEGORY" " + _eltm->getText("Materials.name")).data(), dockspace_id);
            ImGui::DockBuilderFinish(dockspace_id);

            first_times_materials++;
        }

		ImGui::End();
    }

	_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
	_height = size.Y - size.Y/4 - 22;

	if(ImGui::Begin("SceneDockSpace", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground))
    {
		ImGui::SetWindowPos(ImVec2((15 * size.X)/100 - 1, 22 - 1));
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

            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_TYPE_SPECIMEN" " + _eltm->getText("ELTM_Editor.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_SPORTS_ESPORTS" " + _eltm->getText("Scene.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_CODE" " + _eltm->getText("Code.name")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_SETTINGS" " + _eltm->getText("MainMenuBar.options")).data(), dockspace_id);
            ImGui::DockBuilderDockWindow(std::string(AKS_ICON_MD_INFO" " + _eltm->getText("MainMenuBar.about")).data(), dockspace_id);

            ImGui::DockBuilderFinish(dockspace_id);

            first_times_scene++;
        }

		ImGui::End();
    }

    ImGui::PopStyleVar();

    reload_docks = false;
}
