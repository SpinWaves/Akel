// This file is a part of the Akel editor
// CREATED : 28/10/2021
// UPDATED : 28/10/2021

#include <Panels/eltm_editor.h>

ELTM_editor::ELTM_editor(const std::string& name)
{
	_eltm = Ak::make_unique_ptr_w<Ak::ELTM>(Ak::custom_malloc<Ak::ELTM>());
    _name = name;
}

void ELTM_editor::load(const std::string& filename)
{
    _file = filename;
    if(!_eltm->load(filename))
        Ak::Core::log::report(ERROR, "ELTM editor: Couldn't load %s", filename.c_str());
}

void ELTM_editor::render(int width, int height)
{
    _height = height;
    _width = width;
	if(ImGui::Begin(_name.data(), nullptr, ImGuiWindowFlags_NoScrollbar))
    {
		ImGui::SetWindowPos(ImVec2(0, 20), ImGuiCond_FirstUseEver);
		ImGui::SetWindowSize(ImVec2(width, height - 500), ImGuiCond_FirstUseEver);

        editor();

		ImGui::End();
    }
}

void ELTM_editor::editor()
{
    if(ImGui::BeginChild("Scrolling", ImVec2(0, _height - 75), true))
    {
        ImGui::Text("oui");
	    ImGui::EndChild();
    }
}
