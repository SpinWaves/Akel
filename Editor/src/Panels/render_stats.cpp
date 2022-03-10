// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#include <Panels/render_stats.h>

RenderStats::RenderStats(std::shared_ptr<Ak::ELTM> eltm) : Panel("__entities")
{
    _eltm = eltm;
}

void RenderStats::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_width = (19 * size.X)/100;
    _height = size.Y - (50 * size.Y)/100;
	if(ImGui::Begin(_eltm->getLocalText("RenderStats.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
		ImGui::SetWindowPos(ImVec2(size.X - _width, _height));
		ImGui::SetWindowSize(ImVec2(_width, _height));

		ImGui::End();
    }
}
