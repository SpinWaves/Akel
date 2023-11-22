// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 12/03/2022
// Updated : 22/11/2023

#include <Panels/scene.h>
#include <Fonts/material_font.h>
#include <camera_editor.h>

Scene::Scene(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__scene", project)
{
    _eltm = std::move(eltm);
	_play = AkImGui::LoadImage(Ak::VFS::getMainDirPath() / "resources/assets/play.png");

	if(_project.keyExists("scenes"))
	{
		std::filesystem::path main_save = Ak::VFS::getMainDirPath();
		Ak::VFS::replaceMainPath(_project.getDir());
		Ak::SceneManager* manager = static_cast<Ak::SceneManager*>(Ak::getMainAppComponentStack()->get_component("__scenes_manager_component"));
		for(const auto& object : _project.archive()["scenes"])
		{
			std::string name = object["name"];
			_scene = Ak::memAlloc<Ak::Scene>(name);
			manager->add_scene(_scene);
			Ak::SceneSerializer serializer(_scene);
			serializer.deserialize(Ak::VFS::resolve(object["file"]));
			_scene->addCamera<EditorCamera3D>();
		}
		Ak::VFS::replaceMainPath(main_save);
	}
}

void Scene::settingsPage()
{
	ImGui::Text(std::string(AKS_ICON_MD_VIDEOCAM" " + _eltm->getText("Settings.camera")).data());

	ImGui::Separator();

	ImGui::Text(_eltm->getText("Settings.sensitivity").data());
	ImGui::SameLine(0);
	static float sensy = Ak::getMainAppProjectFile().archive()["scene_camera_sensy"];
	ImGui::SliderFloat("##slider_camera_sensy", &sensy, 0.1f, 2.0f, "%.1f");
	if(sensy != Ak::getMainAppProjectFile().archive()["scene_camera_sensy"])
	{
		Ak::getMainAppProjectFile().archive()["scene_camera_sensy"] = sensy;
		static_cast<EditorCamera3D*>(_scene->getCamera().get())->setSensitivity(sensy);
	}
}

void Scene::onUpdate(Ak::Maths::Vec2<int>& size)
{
	static Ak::Vec2i save_size(-1, -1);
	static Ak::SceneManager* manager = static_cast<Ak::SceneManager*>(Ak::getMainAppComponentStack()->get_component("__scenes_manager_component"));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
	if(ImGui::Begin(std::string(AKS_ICON_MD_SPORTS_ESPORTS" " + _eltm->getText("Scene.name")).c_str(), nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar))
	{
		if(size != save_size)
		{
			_scene_texture.destroy();
			_scene_texture = AkImGui::LoadImageEmpty(size.X, size.Y);
			manager->setRenderTarget(_scene_texture.getTextureID());
			save_size = size;
		}
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

		if(ImGui::BeginMenuBar())
		{
			if(ImGui::BeginMenu(std::string(AKS_ICON_MD_ASPECT_RATIO" " + _eltm->getText("Scene.aspect")).c_str()))
			{
				if(ImGui::MenuItem(_eltm->getText("Scene.free_aspect").c_str(), NULL, _aspect_checked == 0))
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
			if(ImGui::BeginMenu(std::string(AKS_ICON_MD_PANORAMA" " + _eltm->getText("Scene.view")).c_str()))
			{
				ImGui::Checkbox(std::string(AKS_ICON_MD_GRID_4X4" " + _eltm->getText("Scene.grid")).c_str(), &_grid);
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		int aspect_width = 0;
		const int window_width = size.X - (15 * size.X) / 100 - (19 * size.X) / 100;
		const int window_height = size.Y - size.Y / 4 - 25;
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
		/*
		ImGuizmo::SetRect(ImGui::GetWindowPos().x + aspect_width, ImGui::GetWindowPos().y - 200, window_width - aspect_width, window_height + 400);

		ImGuizmo::SetDrawlist();

		Ak::Matrixes::perspective(90, aspect, 0.01, 1000);

		if(_grid)
		ImGuizmo::DrawGrid(glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::view)), glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::proj)), glm::value_ptr(glm::mat4(1.0f)), 1000.f);
		ImGuizmo::DrawCubes(glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::view)), glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::proj)), glm::value_ptr(Ak::Matrixes::get_matrix(Ak::matrix::model)), 1);
		*/
		//		draw_list->AddRectFilled(ImVec2((15 * size.X)/100, 0), ImVec2(aspect_width, size.Y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.180f, 0.180f, 0.180f, 1.000f))));
		//		draw_list->AddRectFilled(ImVec2(size.X - (19 * size.X)/100, 0), ImVec2(size.X - (19 * size.X)/100 - aspect_width, size.Y), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.180f, 0.180f, 0.180f, 1.000f))));

		ImGui::Image(_scene_texture.getImGuiID(), ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowWidth()));
		EditorCamera3D::setHover(ImGui::IsItemHovered());

		draw_list->AddRectFilled(ImVec2(ImGui::GetWindowPos().x + window_width - 70, ImGui::GetWindowPos().y + 60), ImVec2(ImGui::GetWindowPos().x + window_width - 22.5, ImGui::GetWindowPos().y + 100), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.3f, 0.3f, 0.3f, 1.f))), 5.0f);
		ImGui::SetCursorPos(ImVec2(window_width - 60, 67));

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.f, 0.f, 0.f, 0.f));
		if(ImGui::ImageButton("##play_button", _play.getImGuiID(), ImVec2(20, 20), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, 1)))
			_run = true;
		ImGui::PopStyleColor(3);

		ImGui::End();
	}
	ImGui::PopStyleVar();
}

void Scene::onQuit()
{
	_scene_texture.destroy();
	_play.destroy();
}
