// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 29/05/2023

#ifndef __AK_STUDIO_LAUNCHER_COMPONENT__
#define __AK_STUDIO_LAUNCHER_COMPONENT__

#include <Akel.h>
#include <Fonts/material_font.h>

using json = nlohmann::json;

struct Project
{
	AkImGui::ImImage icon;
	std::string title;
	std::filesystem::path folder;
	bool akel_filesystem = true;

	Project(AkImGui::ImImage i, std::string t, std::filesystem::path p, bool a) :
		icon(std::move(i)), title(std::move(t)), folder(std::move(p)), akel_filesystem(a)
	{}

	inline bool operator==(const Project& rhs) const { return title == rhs.title && folder == rhs.folder; }
};

namespace std
{
	template <>
	struct hash<Project>
	{
		size_t operator()(const Project& p) const noexcept
		{
			return std::hash<std::string>()(p.title) + std::hash<std::string>()(p.folder.string());
		}
	};
}

void launchAkelStudio();

class LauncherComponent : public Ak::Component
{
	public:
		LauncherComponent();

		void onAttach() override;
		void onImGuiRender() override;
		void onEvent(Ak::Input& input) override;
		void onQuit() override;

		void generateFontTextures(Ak::ImGuiComponent* imgui);

		~LauncherComponent() = default;
	
	private:
		void drawMainContent();
		void drawSideBar();

	private:
		std::unordered_set<Project> _projects;
		json _json;
		std::optional<Project> _currently_creating;
		AkImGui::ImImage _logo;
		ImFont* _tiny_font = nullptr;
		ImFont* _title_font = nullptr;
		bool _new_project_window = false;
		bool _error_no_name = false;
		bool _error_no_path = false;
		bool _warn_not_empty = false;
};

#endif
