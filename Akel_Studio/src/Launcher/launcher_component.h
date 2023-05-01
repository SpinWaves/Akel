// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 01/05/2023

#ifndef __AK_STUDIO_LAUNCHER_COMPONENT__
#define __AK_STUDIO_LAUNCHER_COMPONENT__

#include <Akel.h>
#include <Fonts/material_font.h>

struct Project
{
	AkImGui::ImImage icon;
	std::string title;
	std::string description;

	Project(AkImGui::ImImage i, std::string t, std::string d) :
		icon(std::move(i)), title(std::move(t)), description(std::move(d))
	{}

	inline bool operator==(const Project& rhs) const { return title == rhs.title; }
};

namespace std
{
	template <>
	struct hash<Project>
	{
		size_t operator()(const Project& p) const noexcept
		{
			return std::hash<std::string>()(p.title);
		}
	};
}

class LauncherComponent : public Ak::Component
{
	public:
		LauncherComponent() = default;

		void onAttach() override;
		void onImGuiRender() override;
		void onImGuiEvent(Ak::Input& input) override;
		void onQuit() override;

		void generateFontTextures(Ak::ImGuiComponent* imgui);

		~LauncherComponent() = default;
	
	public:

	private:
		void drawMainContent();
		void drawSideBar();

	private:
		std::unordered_set<Project> _projects;
		AkImGui::ImImage _logo;
		ImFont* _tiny_font = nullptr;
		ImFont* _title_font = nullptr;
};

#endif
