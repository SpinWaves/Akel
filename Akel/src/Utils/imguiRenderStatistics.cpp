// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 07/02/2023

#include <Utils/imguiRenderStatistics.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	ImGuiRenderStats::ImGuiRenderStats(RendererComponent* renderer) : ImGuiComponent(renderer) {}

	void ImGuiRenderStats::onImGuiRender()
	{
		if(ImGui::Begin("Render Statistics", nullptr, ImGuiWindowFlags_NoResize))
		{
			ImGui::Text("youpi pouyic");
			ImGui::End();
		}
	}
}
