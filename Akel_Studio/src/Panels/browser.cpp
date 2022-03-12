// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 12/03/2022

#include <Panels/browser.h>

Browser::Browser(std::shared_ptr<Ak::ELTM> eltm) : Panel("__browser")
{
    _eltm = eltm;
}

void Browser::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = size.X - (15 * size.X)/100 - (19 * size.X)/100;
	_height = size.Y / 4;
    
	if(ImGui::Begin(_eltm->getLocalText("Browser.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
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
        if(ImGui::Button("   ../   "))
        {
            size_t found = 0;
            if((found = _parent.rfind('/', _parent.length() - 2)) != std::string::npos)
                _parent.erase(_parent.begin() + found + 1, _parent.end());
            _files.clear(); 
        }
        ImGui::Separator();
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
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
    std::string size_string = std::to_string((int)mantissa);
    size_string.push_back(' ');
    size_string.push_back("BKMGTPE"[i]);
    if(size_string.back() != 'B')
        size_string.append("bytes");
    return std::move(size_string);
}

void Browser::content()
{
    size_t found = 0;
    std::string filename;
    if(ImGui::BeginChild("Content", ImVec2((83 * _width)/100, _height - 41), true, ImGuiWindowFlags_HorizontalScrollbar))
    {
        ImGui::Text(_eltm->getLocalText("Browser.content").c_str());
        ImGui::Separator();
        for(const std::filesystem::directory_entry& file : _files)
        {
            ImGui::Indent(5);
            
            filename = file.path().string();
            if((found = filename.rfind("/")) != std::string::npos)
                filename.erase(filename.begin(), filename.begin() + found + 1);
            
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
        if(ImGui::TreeNodeEx(dire.c_str(), !is_there_subdir(full_path + '/' + dire) ? ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_Framed))
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
