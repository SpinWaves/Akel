// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 30/10/2023

#include <Panels/browser.h>
#include <Fonts/material_font.h>

bool is_binaries(const std::filesystem::path& file)
{
	return	(std::filesystem::status(file).permissions() & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ||
			(std::filesystem::status(file).permissions() & std::filesystem::perms::group_exec) != std::filesystem::perms::none ||
			(std::filesystem::status(file).permissions() & std::filesystem::perms::others_exec) != std::filesystem::perms::none;
}

bool is_sound_file(const std::filesystem::path& file)
{
	static const std::unordered_set<std::string> extensions{
		".mp3",
		".wav",
		".ogg",
		".flac",
		".m4a",
	};
	return extensions.find(file.extension().string()) != extensions.end();
}

bool is_image_file(const std::filesystem::path& file)
{
	static const std::unordered_set<std::string> extensions{
		".jpg",
		".jpeg",
		".gif",
		".png",
		".bmp",
		".xpm",
		".pcx",
		".pnm",
		".tga",
		".tiff",
		".tif",
		".lbm",
		".iff",
		".ico",
	};
	return extensions.find(file.extension().string()) != extensions.end();
}

bool is_script_file(const std::filesystem::path& file)
{
	static const std::unordered_set<std::string> extensions{
		".lua",
		".ksl",
		".kila",
		".cpp",
		".cxx",
		".cc",
		".h",
		".hpp",
		".hxx",
		".spv",
		".glsl",
		".frag",
		".vert",
		".nzsl",
	};
	return extensions.find(file.extension().string()) != extensions.end();
}


bool is_there_subdir(const std::filesystem::path& path)
{
	std::size_t found = 0;
	for(auto const& dir_entry : std::filesystem::directory_iterator(path))
	{
		std::string sdir = dir_entry.path().string();
		if((found = sdir.rfind("/")) != std::string::npos)
			sdir.erase(sdir.begin(), sdir.begin() + found + 1);

		if(sdir[0] == '.') // hidden files/dirs
			continue;

		if(dir_entry.is_directory())
			return true;
	}
	return false;
}

Browser::Browser(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__browser", project)
{
    _eltm = std::move(eltm);
	_current_path = project.getDir();

	ImGuiIO& io = ImGui::GetIO();
	static const ImWchar icons_ranges[] = { AKS_ICON_MIN_MD, AKS_ICON_MAX_16_MD, 0 };
	_big_icons_font = io.Fonts->AddFontFromFileTTF(Ak::VFS::resolve(":/resources/fonts/material_icons-regular.ttf").string().c_str(), 60.0f, nullptr, icons_ranges);
}

void Browser::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
	_height = size.Y / 4;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(2.f, 2.f));
	if(ImGui::Begin(std::string(AKS_ICON_MD_FOLDER_OPEN" " + _eltm->getText("Browser.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.f);
		ImGui::PushStyleVar(ImGuiStyleVar_SeparatorTextPadding, ImVec2(4.f, 1.f));
			browser();
			ImGui::SameLine((15.1 * _width) / 100 + 5);
			content();
		ImGui::PopStyleVar(2);

		ImGui::End();
    }
	ImGui::PopStyleVar();
}

void Browser::browser()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 10.0f);
	if(ImGui::BeginChild("Browser", ImVec2((15.1 * _width)/100, _height - 27), true, ImGuiWindowFlags_HorizontalScrollbar))
	{
		ImGui::Text(std::string(AKS_ICON_MD_FOLDER_COPY" " + _eltm->getText("Browser.folders")).c_str());
		ImGui::SameLine((15.1 * _width) / 100 - 40);
		if(ImGui::SmallButton(" ../ "))
			_current_path = _current_path.parent_path();
		
		ImGui::Separator();

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
			diveInDirectory(_current_path);
		ImGui::PopStyleVar();

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
}

void Browser::diveInDirectory(const std::filesystem::path& path)
{
	for(const auto& dir_entry : std::filesystem::directory_iterator(path)) 
	{
		std::filesystem::path dir_path = dir_entry.path();
		if(!std::filesystem::is_directory(dir_path) || dir_path.filename().string()[0] == '.')
			continue;
		if(ImGui::TreeNodeEx(std::string(AKS_ICON_MD_FOLDER" " + dir_path.filename().string()).c_str(), ImGuiTreeNodeFlags_SpanFullWidth | (!is_there_subdir(dir_path) ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow)))
		{
			diveInDirectory(dir_path);
			ImGui::TreePop();
		}
		if(ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered(ImGuiHoveredFlags_None))
			_current_path /= dir_path;
	}
}

void Browser::content()
{
    if(ImGui::BeginChild("Content", ImVec2((84.25 * _width)/100, _height - 27), true, ImGuiWindowFlags_HorizontalScrollbar))
    {
        ImGui::Text(std::string(AKS_ICON_MD_FILE_COPY" " + _eltm->getText("Browser.content")).c_str());
		ImGui::Separator();
		for(const auto& dir_entry : std::filesystem::directory_iterator(_current_path)) 
		{
			std::filesystem::path dir_path = dir_entry.path();
			if(!std::filesystem::is_directory(dir_path) && dir_path.filename().string()[0] != '.')
			{
				contentChild(dir_path);
				ImGui::SameLine();
			}
		}
	    ImGui::EndChild();
    }
}

void Browser::contentChild(const std::filesystem::path& path)
{
	if(ImGui::BeginChild(path.string().c_str(), ImVec2(75, 100), true))
	{
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
		draw_list->AddRectFilled(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + 75, ImGui::GetWindowPos().y + 70), ImGui::GetColorU32(ImGui::ColorConvertFloat4ToU32(ImVec4(0.3f, 0.3f, 0.3f, 1.f))), 0.f);
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 60.f) * 0.5f);
		ImGui::PushFont(_big_icons_font);
		if(is_image_file(path))
			ImGui::TextUnformatted(AKS_ICON_MD_IMAGE);
		else if(is_sound_file(path))
			ImGui::TextUnformatted(AKS_ICON_MD_AUDIO_FILE);
		else if(is_binaries(path))
			ImGui::TextUnformatted(AKS_ICON_MD_TERMINAL);
		else if(is_script_file(path))
			ImGui::TextUnformatted(AKS_ICON_MD_CODE);
		else
			ImGui::TextUnformatted(AKS_ICON_MD_INSERT_DRIVE_FILE);
		ImGui::PopFont();
		ImGui::TextUnformatted(path.filename().string().c_str());
		ImGui::EndChild();
	}
}
