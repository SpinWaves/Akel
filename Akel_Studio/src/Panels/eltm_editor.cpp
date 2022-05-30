// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 28/10/2021
// Updated : 30/05/2022

#include <Panels/eltm_editor.h>

ELTM_editor::ELTM_editor(const std::string& name, std::string* input_buffer) : Panel("__eltm_editor")
{
	_eltm = Ak::make_shared_ptr_w<Ak::ELTM>(Ak::memAlloc<Ak::ELTM>(true));
    _name = name;
    _input_buffer = input_buffer;
}

void ELTM_editor::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(!_input_buffer->empty())
    {
        if(!_eltm->load(*_input_buffer))
            Ak::Core::log::report(ERROR, "ELTM editor: Couldn't load %s", _input_buffer->c_str());
    }
    if(!_is_open)
        return;

	if(ImGui::Begin(_name.data(), &_is_open, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
        editor();

		ImGui::End();
    }
}

void ELTM_editor::editor()
{
    if(ImGui::BeginChild("Scrolling", ImVec2(0, _height - 75), true))
    {
        for(auto it = _eltm->getCurrentTexts().begin(); it!= _eltm->getCurrentTexts().end(); it++)
			ImGui::TextUnformatted(std::string(it->first + " : " + it->second).data());
        for(auto it = _eltm->getCurrentModules().begin(); it!= _eltm->getCurrentModules().end(); it++)
            for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
			    ImGui::TextUnformatted(std::string(it->first + "." + it2->first + " : " + it2->second).data());
	    ImGui::EndChild();
    }

    ImGui::Separator();
}
