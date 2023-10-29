// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 29/10/2023

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
	return	extensions.find(file.extension().string()) != extensions.end();
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
	return	extensions.find(file.extension().string()) != extensions.end();
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

std::string Browser::getSize(std::uintmax_t size)
{
	double mantissa = size;
	int i = 0;
	for(; mantissa >= 1024.0; i++)
		mantissa /= 1024.0;

	mantissa = std::ceil(mantissa * 10.0) / 10.;

	std::ostringstream out;
	out.precision(2);
	out << std::fixed << mantissa;
	std::string size_string = out.str();

	size_string.push_back(' ');
	if(i != 0)
		size_string.push_back("KMGTPE"[i - 1]);
	size_string.append("bytes");
	return size_string;
}

void Browser::content()
{
    if(ImGui::BeginChild("Content", ImVec2((84.25 * _width)/100, _height - 27), true, ImGuiWindowFlags_HorizontalScrollbar))
    {
        ImGui::Text(std::string(AKS_ICON_MD_FILE_COPY" " + _eltm->getText("Browser.content")).c_str());
        ImGui::Separator();
	    ImGui::EndChild();
    }
}
