// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 27/08/2022

#include <Panels/browser.h>
#include <Fonts/material_font.h>

Browser::Browser(std::shared_ptr<Ak::ELTM> eltm) : Panel("__browser")
{
    _eltm = std::move(eltm);
}

void Browser::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
	_height = size.Y / 4;
    
	if(ImGui::Begin(std::string(AKS_ICON_MD_FOLDER_OPEN" " + _eltm->getText("Browser.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
        browser();
        ImGui::SameLine(0);
        content();

		ImGui::End();
    }
}

void Browser::browser()
{
    if(ImGui::BeginChild("Browser", ImVec2((15.1 * _width)/100, _height - 41), true, ImGuiWindowFlags_HorizontalScrollbar))
    {
		ImGui::Text(std::string(AKS_ICON_MD_FOLDER_COPY" " + _eltm->getText("Browser.folders")).c_str());
        ImGui::SameLine((15.1 * _width)/100 - 60);
        if(ImGui::Button("   ../   "))
        {
            size_t found = 0;
            if((found = _parent.rfind('/', _parent.length() - 2)) != std::string::npos)
                _parent.erase(_parent.begin() + found + 1, _parent.end());
            _files.clear(); 
        }
        ImGui::Separator();
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
            dir(_parent);
        ImGui::PopStyleVar();

	    ImGui::EndChild();
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

bool is_binaries(std::filesystem::path file)
{
	return	(std::filesystem::status(file).permissions() & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ||
			(std::filesystem::status(file).permissions() & std::filesystem::perms::group_exec) != std::filesystem::perms::none ||
			(std::filesystem::status(file).permissions() & std::filesystem::perms::others_exec) != std::filesystem::perms::none;
}

bool is_sound_file(std::filesystem::path file)
{
	return	file.extension().string() == ".mp3" || file.extension().string() == ".wav" || file.extension().string() == ".ogg" || file.extension().string() == ".flac" ||
			file.extension().string() == ".m4a";
}

bool is_image_file(std::filesystem::path file)
{
	return	file.extension().string() == ".jpg" || file.extension().string() == ".jpeg" || file.extension().string() == ".gif" || file.extension().string() == ".png" ||
			file.extension().string() == ".bmp" || file.extension().string() == ".xpm" || file.extension().string() == ".pcx" || file.extension().string() == ".pnm" ||
			file.extension().string() == ".tga" || file.extension().string() == ".tiff" || file.extension().string() == ".tif" || file.extension().string() == ".lbm" ||
			file.extension().string() == ".iff" || file.extension().string() == ".ico";
}

bool is_script_file(std::filesystem::path file)
{
	return	file.extension().string() == ".lua" || file.extension().string() == ".ksl" || file.extension().string() == ".kila" || file.extension().string() == ".cpp" ||
			file.extension().string() == ".cxx" || file.extension().string() == ".cc" || file.extension().string() == ".h" || file.extension().string() == ".hpp" ||
			file.extension().string() == ".hxx" || file.extension().string() == ".spv" || file.extension().string() == ".glsl" || file.extension().string() == ".frag" ||
			file.extension().string() == ".vert";
}

void Browser::content()
{
    size_t found = 0;
    std::string filename;
    if(ImGui::BeginChild("Content", ImVec2((83 * _width)/100, _height - 41), true, ImGuiWindowFlags_HorizontalScrollbar))
    {
        ImGui::Text(std::string(AKS_ICON_MD_FILE_COPY" " + _eltm->getText("Browser.content")).c_str());
        ImGui::SameLine((83 * _width)/100 - 40);
		if(ImGui::Button(AKS_ICON_MD_SETTINGS))
		{

		}
        ImGui::Separator();
        for(const std::filesystem::directory_entry& file : _files)
        {
            ImGui::Indent(5);
            
            filename = file.path().string();
            if((found = filename.rfind("/")) != std::string::npos)
                filename.erase(filename.begin(), filename.begin() + found + 1);

			if(std::filesystem::is_regular_file(file))
			{
				if(is_binaries(file))
					filename.insert(0, AKS_ICON_MD_TERMINAL" ");
				else if(is_sound_file(file))
					filename.insert(0, AKS_ICON_MD_AUDIO_FILE" ");
				else if(is_image_file(file))
					filename.insert(0, AKS_ICON_MD_IMAGE" ");
				else if(is_script_file(file))
					filename.insert(0, AKS_ICON_MD_CODE" ");
				else if(file.path().extension().string() == ".eltm" || file.path().extension().string() == ".tm")
					filename.insert(0, AKS_ICON_MD_TYPE_SPECIMEN" ");
				else if(file.path().extension().string() == ".akel")
					filename.insert(0, AKS_ICON_MD_SETTINGS_APPLICATIONS" ");
				else if(file.path().filename().string() == "LICENSE")
					filename.insert(0, AKS_ICON_MD_COPYRIGHT" ");
				else
					filename.insert(0, AKS_ICON_MD_DESCRIPTION" ");
			}
			else if(std::filesystem::is_symlink(file))
				filename.insert(0, AKS_ICON_MD_LINK" ");
            
            if(ImGui::Selectable(filename.c_str(), _current_file == file.path().string()))
                _current_file = file.path().string();
            ImGui::SameLine(300);
            ImGui::Text(getSize(file.file_size()).c_str());
            ImGui::Unindent(5);
        }
	    ImGui::EndChild();
    }
}

void Browser::dir(std::string directory)
{
    std::string full_path = directory.c_str();
    size_t found = 0;
    std::set<std::string> dirs;

    for(auto const& dir_entry : std::filesystem::directory_iterator(directory))
    {
        directory = dir_entry.path().string();
        if((found = directory.rfind("/")) != std::string::npos)
            directory.erase(directory.begin(), directory.begin() + found + 1);
        
        if(directory[0] == '.') // hidden files/dirs
            continue;
        
        if(dir_entry.is_directory())
            dirs.insert(directory);
        else if(full_path == _parent)
            _files.insert(dir_entry);
    }
    for(const std::string& dire : dirs)
    {
        if(ImGui::TreeNodeEx(std::string(AKS_ICON_MD_FOLDER" " + dire).c_str(), ImGuiTreeNodeFlags_SpanFullWidth | (!is_there_subdir(full_path + '/' + dire) ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow)))
        {
            dir(std::move(std::string(full_path + "/" + dire)));
            ImGui::TreePop();
        }
        if(ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered(ImGuiHoveredFlags_None))
        {
            _parent = full_path + "/" + dire + "/";
            _files.clear();
        }
    }
}

bool Browser::is_there_subdir(std::string dir)
{
    size_t found = 0;
    for(auto const& dir_entry : std::filesystem::directory_iterator(dir))
    {
        dir = dir_entry.path().string();
        if((found = dir.rfind("/")) != std::string::npos)
            dir.erase(dir.begin(), dir.begin() + found + 1);
        
        if(dir[0] == '.') // hidden files/dirs
            continue;
        
        if(dir_entry.is_directory())
            return true;
    }
    return false;
}
