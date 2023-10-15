// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 15/10/2023
/*
#include <Utils/imguiRenderStatistics.h>
#include <Renderer/rendererComponent.h>
#include <Core/gpu.h>

namespace Ak
{
	ImGuiRenderStats::ImGuiRenderStats(RendererComponent* renderer) : ImGuiComponent(renderer) {}

	void ImGuiRenderStats::onRender()
	{
		static Core::GPU gpu;
		ImGui::SetNextWindowPos(ImVec2(20, 20));
		ImGui::SetNextWindowSize(ImVec2(300, 200));
		if(ImGui::Begin("Render Statistics", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::Text("Vulkan version : %s", gpu.getVulkanVersion().c_str());
			ImGui::Text("Number of devices : %d", gpu.getNumberOfDevices());
			ImGui::Separator();
			ImGui::Text("GPU in use : %s", gpu.getModelName().c_str());
			ImGui::Text("GPU Vendor : %s", gpu.getVendorName().c_str());
			ImGui::Text("GPU type : %s", gpu.getDeviceType().c_str());
			ImGui::Separator();
			ImGui::Text("FPS : %d", _renderer->getFPS());
			ImGui::End();
		}
	}
}
*/
