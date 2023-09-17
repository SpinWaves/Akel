// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 17/09/2023

#include "launcher_component.h"

static bool quit = false;

SDL_HitTestResult hitTestCallback(SDL_Window* win, const SDL_Point* area, void* data)
{
	if(area->y < 63 && !*static_cast<bool*>(data))
		return SDL_HITTEST_DRAGGABLE;
	return SDL_HITTEST_NORMAL;
}

#if defined(AK_PLATFORM_LINUX) || defined(AK_PLATFORM_OSX)
	extern char** environ;
#elif defined(AK_PLATFORM_WINDOWS)
	extern char** _environ;
#endif

static std::filesystem::path akel_studio_project;

void launchAkelStudio()
{
	if(akel_studio_project.empty())
		return;
	std::string project = akel_studio_project.string();
#if defined(AK_PLATFORM_LINUX) || defined(AK_PLATFORM_OSX)
	std::string path = Ak::VFS::getMainDirPath() / "akelstudio_application";
	char* args[] = { const_cast<char*>(path.c_str()), const_cast<char*>(project.c_str()), nullptr };
	execve(path.c_str(), args, environ);
#elif defined(AK_PLATFORM_WINDOWS)
	std::string path = std::filesystem::path(Ak::VFS::getMainDirPath() / "akelstudio_application.exe").string();
	char* args[] = { const_cast<char*>(path.c_str()), const_cast<char*>(project.c_str()), nullptr };
	_execve(path.c_str(), args, _environ);
#else
	#error "Akel Studio is only supported on Linux, MacOS_X and Windows"
#endif
}

LauncherComponent::LauncherComponent() : Ak::Component("launcherComponent") {}

void LauncherComponent::onAttach()
{
	_logo = AkImGui::LoadImage(Ak::VFS::getMainDirPath() / "resources/assets/logo.png");

	ImGuiIO& io = ImGui::GetIO();
	_tiny_font = io.Fonts->AddFontFromFileTTF(std::filesystem::path(Ak::VFS::getMainDirPath() / "resources/fonts/opensans/OpenSans-Regular.ttf").string().c_str(), 15.0f);
	_title_font = io.Fonts->AddFontFromFileTTF(std::filesystem::path(Ak::VFS::getMainDirPath() / "resources/fonts/opensans/OpenSans-Regular.ttf").string().c_str(), 45.0f);

	std::filesystem::path project_list = Ak::VFS::getMainDirPath() / "settings/project_list.json";
	if(std::filesystem::exists(project_list))
	{
		std::ifstream file(project_list);
		if(!file.is_open())
		{
			Ak::Error("Akel Studio Launcher : unable to open project list file");
			return;
		}
		_json = json::parse(file);
		for(json::iterator it = _json.begin(); it != _json.end(); ++it)
		{
			if(it.value()["icon"] == "default")
				_projects.emplace(AkImGui::LoadImage(Ak::VFS::getMainDirPath() / "resources/assets/logo_icon.png"), it.value()["title"], it.key(), false);
			else
				_projects.emplace(AkImGui::LoadImage(it.value()["icon"]), it.value()["title"], it.key(), false);
		}
	}
	Ak::WindowComponent* window = Ak::getMainAppComponentStack()->get_component_as<Ak::WindowComponent*>("__window_component");
	SDL_SetWindowHitTest(window->getNativeWindow(), hitTestCallback, &_new_project_window);
}

void LauncherComponent::onRender()
{
	static Ak::WindowComponent* window = Ak::getMainAppComponentStack()->get_component_as<Ak::WindowComponent*>("__window_component");
	if(ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking))
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(window->size.X, window->size.Y));

		ImGui::Image(_logo.getImGuiID(), ImVec2(50, 50));
		ImGui::SameLine();
		ImGui::PushFont(_title_font);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
		ImGui::Text("Akel Studio");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		
		drawMainContent();
		ImGui::SameLine();
		drawSideBar();

		ImGui::End();
	}
}

void LauncherComponent::onEvent(Ak::Input& input)
{
	if(quit)
		input.finish();
}

void LauncherComponent::onQuit()
{
	_logo.destroy();
	std::ofstream o(Ak::VFS::getMainDirPath() / "settings/project_list.json");
	o << std::setw(4) << _json << std::endl;
	for(const Project& project : _projects)
		const_cast<Project&>(project).icon.destroy();
}

void LauncherComponent::drawMainContent()
{
	constexpr ImVec2 child_size = ImVec2(585, 65);
	static int32_t selector = -1;

	if(ImGui::BeginChild("main_content", ImVec2(600, 0), true))
	{
		int i = 0;
		for(auto it = _projects.begin(); it != _projects.end(); i++)
		{
			bool has_been_pushed = false;
			bool has_been_deleted = false;
			if(selector == i && !_new_project_window)
			{
				if(ImGui::IsMouseDown(ImGuiPopupFlags_MouseButtonLeft))
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.3f, 0.3f, 0.3f, 1.f));
				else if(ImGui::IsMouseReleased(ImGuiPopupFlags_MouseButtonLeft))
				{
					akel_studio_project = it->folder;
					quit = true;
				}
				else
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.f));
				has_been_pushed = true;
			}
			if(ImGui::BeginChild(it->folder.string().c_str(), child_size, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
			{
				if(ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows))
					selector = i;
				else if(i == selector)
					selector = -1;

				ImGui::Image(const_cast<Project&>(*it).icon.getImGuiID(), ImVec2(50, 50));
				ImGui::SameLine();

				if(ImGui::BeginChild(std::string(it->folder.string() + "_intenal").c_str(), ImVec2(child_size.x - 120, 0), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground))
				{
					ImGui::TextUnformatted(it->title.c_str());

					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
							ImGui::TextUnformatted(it->folder.parent_path().string().c_str());
						ImGui::PopStyleColor();
					ImGui::PopFont();

					ImGui::EndChild();
				}
				ImGui::SameLine();
				if(ImGui::Button(AKS_ICON_MD_MORE_VERT))
					ImGui::OpenPopup("more");
				if(ImGui::IsItemHovered())
					selector = -1;

				if(ImGui::BeginPopup("more"))
				{
					selector = -1;
					if(ImGui::MenuItem("Delete"))
					{
						_json.erase(it->folder);
						it = _projects.erase(it);
						has_been_deleted = true;
					}
					ImGui::EndPopup();
				}
				ImGui::EndChild();
			}
			if(has_been_pushed)
				ImGui::PopStyleColor();
			if(!has_been_deleted)
				++it;
			if(it != _projects.end())
				ImGui::Separator();
		}
		ImGui::EndChild();
	}
}

void LauncherComponent::drawSideBar()
{
	if(ImGui::BeginChild("side_content", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
	{
		if(ImGui::Button(AKS_ICON_MD_CREATE_NEW_FOLDER " New Project", ImVec2(ImGui::GetWindowWidth() - 18, 0)))
		{
			if(!_new_project_window)
			{
				if(_currently_creating.has_value())
					_currently_creating.reset();
				_error_no_name = false;
				_error_no_name = false;
				_warn_not_empty = false;
				_currently_creating.emplace(AkImGui::LoadImage(Ak::VFS::getMainDirPath() / "resources/assets/logo_icon.png"), "", "", true);
			}
			_new_project_window = true;
		}
		if(ImGui::Button(AKS_ICON_MD_FILE_DOWNLOAD " Import Project", ImVec2(ImGui::GetWindowWidth() - 18, 0)))
		{
			auto file = pfd::open_file("Import Project", "", { "Akel projects (.akel)", "*.akel" }).result();
			if(!file.empty())
			{
				std::filesystem::path path = file[0];
				if(std::filesystem::is_directory(path))
				{
					_projects.emplace(AkImGui::LoadImage(Ak::VFS::getMainDirPath() / "resources/assets/logo_icon.png"), path.string(), path, false);
					_json[path.string()]["title"] = path.string();
				}
				else
				{
					_projects.emplace(AkImGui::LoadImage(Ak::VFS::getMainDirPath() / "resources/assets/logo_icon.png"), path.stem().string(), path, false);
					_json[path.string()]["title"] = path.stem().string();
				}
				_json[path.string()]["icon"] = "default";
			}
		}

		ImGui::Separator();

		if(ImGui::Button(AKS_ICON_MD_DELETE " Clear Project List", ImVec2(ImGui::GetWindowWidth() - 18, 0)))
		{
			_projects.clear();
			_json.clear();
		}
		if(ImGui::Button("Quit", ImVec2(ImGui::GetWindowWidth() - 18, 0)))
			quit = true;

		ImGui::Dummy(ImVec2(10, ImGui::GetWindowHeight() - ImGui::GetCursorPosY() - ImGui::GetTextLineHeightWithSpacing() * 2));
		ImGui::Separator();

		ImGui::PushFont(_tiny_font);
			ImGui::Text("Akel Version " AK_VERSION_STR);
			ImGui::Text("Akel Studio Version 0.0.1");
		ImGui::PopFont();

		ImGui::EndChild();
	}

	if(_new_project_window)
	{
		static Ak::WindowComponent* window = Ak::getMainAppComponentStack()->get_component_as<Ak::WindowComponent*>("__window_component");
		ImGui::SetNextWindowPos(ImVec2(window->size.X / 2.0f - 200.0f, window->size.Y / 2.0f - 150.0f), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(400.0f, 300.0f));
		ImGui::SetNextWindowFocus();
		if(ImGui::Begin(AKS_ICON_MD_CREATE_NEW_FOLDER " New Project", &_new_project_window, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
		{
			if(ImGui::BeginChild("##new_project_child", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
			{
				ImGui::TextUnformatted("Project's Name :");
				if(_error_no_name)
				{
					ImGui::SameLine();
					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.365f, 0.365f, 1.0f));
							ImGui::TextUnformatted("Your project needs a name !");
						ImGui::PopStyleColor();
					ImGui::PopFont();
				}
				if(AkImGui::InputTextWithHint("##project_name", "New Project", &_currently_creating->title, ImGuiInputTextFlags_AutoSelectAll))
					_error_no_name = false;

				ImGui::TextUnformatted("Project's Folder :");
				if(!_currently_creating->folder.empty())
					_error_no_path = false;
				if(_error_no_path)
				{
					ImGui::SameLine();
					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.365f, 0.365f, 1.0f));
							ImGui::TextUnformatted("Your project needs a folder !");
						ImGui::PopStyleColor();
					ImGui::PopFont();
				}
				else if(!_currently_creating->folder.empty() && !std::filesystem::is_empty(_currently_creating->folder))
				{
					ImGui::SameLine();
					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 0.f, 1.f));
							ImGui::TextUnformatted("This file is not empty, be warn");
						ImGui::PopStyleColor();
					ImGui::PopFont();
				}

				if(!_currently_creating->folder.empty())
				{
					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
							ImGui::TextUnformatted(_currently_creating->folder.string().c_str());
						ImGui::PopStyleColor();
					ImGui::PopFont();
				}
				if(ImGui::Button("Select Folder"))
				{
					auto dialog = pfd::select_folder("Select project folder", "", pfd::opt::force_path);
					_currently_creating->folder = dialog.result();
				}

				ImGui::NewLine();

				ImGui::TextUnformatted("Use Akel's directories architecture");
				ImGui::SameLine();
				ImGui::Checkbox("##dir_arch", &_currently_creating->akel_filesystem);

				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - (ImGui::GetFontSize() * 2.0f) - 10);

				if(ImGui::Button(AKS_ICON_MD_NOTE_ADD " Create Project And Setup Folder", ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetFontSize() * 2.0f)))
				{
					if(_currently_creating->title.empty())
						_error_no_name = true;
					else if(_currently_creating->folder.empty())
						_error_no_path = true;
					else
					{
						std::ofstream project_file(_currently_creating->folder / (_currently_creating->title + ".akel"));
						project_file << "{}" << std::endl;
						if(_currently_creating->akel_filesystem)
						{
							std::filesystem::path res = _currently_creating->folder / "Resources";
							std::filesystem::create_directory(res);
							std::filesystem::create_directory(res / "Textures");
							std::filesystem::create_directory(res / "Meshes");
							std::filesystem::create_directory(res / "Scripts");
							std::filesystem::create_directory(res / "Scenes");
							std::filesystem::create_directory(res / "Sounds");
						}
						_projects.insert(*_currently_creating);
						_json[(_currently_creating->folder / (_currently_creating->title + ".akel")).string()]["title"] = _currently_creating->title;
						_json[(_currently_creating->folder / (_currently_creating->title + ".akel")).string()]["icon"] = "default";
						_new_project_window = false;
					}
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}
	}
}

void LauncherComponent::generateFontTextures(Ak::ImGuiComponent* imgui)
{
	ImGuiIO& io = ImGui::GetIO();
	imgui->addFontFromFile(std::filesystem::path(Ak::VFS::getMainDirPath() / "resources/fonts/opensans/OpenSans-Regular.ttf").string().c_str(), 18.0f, true);
	static const ImWchar icons_ranges[] = { AKS_ICON_MIN_MD, AKS_ICON_MAX_16_MD, 0 };
	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphOffset.y = 4.0f;

	io.Fonts->AddFontFromFileTTF(std::filesystem::path(Ak::VFS::getMainDirPath() / "resources/fonts/material_icons-regular.ttf").string().c_str(), 18.0f, &config, icons_ranges);
	io.Fonts->AddFontDefault();
	imgui->generateFonts();
}
