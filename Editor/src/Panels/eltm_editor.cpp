// This file is a part of the Akel editor
// CREATED : 28/10/2021
// UPDATED : 07/11/2021

#include <Panels/eltm_editor.h>

ELTM_editor::ELTM_editor(const std::string& name)
{
	_eltm = Ak::make_unique_ptr_w<Ak::ELTM>(Ak::custom_malloc<Ak::ELTM>(true));
    _name = name;
}

void ELTM_editor::load(const std::string& filename)
{
    _file = filename;
    if(!_eltm->load(filename))
        Ak::Core::log::report(ERROR, "ELTM editor: Couldn't load %s", filename.c_str());
}

void ELTM_editor::open()
{
    _is_open = _is_open ? false : true;
}

void ELTM_editor::render(int width, int height)
{
    _height = height;
    _width = width;
	if(ImGui::Begin(_name.data(), &_is_open))
    {
		ImGui::SetWindowPos(ImVec2(50, 500), ImGuiCond_FirstUseEver);
		ImGui::SetWindowSize(ImVec2(width - 100, height - 500), ImGuiCond_FirstUseEver);

        editor();

		ImGui::End();
    }
}

void ELTM_editor::editor()
{
    if(ImGui::BeginChild("Scrolling", ImVec2(0, _height - 600), true))
    {
        for(auto it = _eltm->getCurrentTexts().begin(); it!= _eltm->getCurrentTexts().end(); it++)
        {
			ImGui::TextUnformatted(std::string(it->first + " : " + it->second).data());
        }
        for(auto it = _eltm->getCurrentModules().begin(); it!= _eltm->getCurrentModules().end(); it++)
        {
            for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
			    ImGui::TextUnformatted(std::string(it->first + "." + it2->first + " : " + it2->second).data());
        }
	    ImGui::EndChild();
    }

    ImGui::Separator();
}
