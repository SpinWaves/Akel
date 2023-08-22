// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 22/08/2023

#include <Panels/renderer_manager.h>
#include <Fonts/material_font.h>

RendererManager::RendererManager(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__renderer_manager", project), _gpu()
{
	_eltm = std::move(eltm);
	int cull_mode = Ak::getMainAppProjectFile().archive()["cullmode"];
	switch(cull_mode)
	{
		case VK_CULL_MODE_NONE: selected = _eltm->getText("RendererManager.cull_none"); break;
		case VK_CULL_MODE_FRONT_BIT: selected = _eltm->getText("RendererManager.cull_front"); break;
		case VK_CULL_MODE_BACK_BIT: selected = _eltm->getText("RendererManager.cull_back"); break;
		case VK_CULL_MODE_FRONT_AND_BACK: selected = _eltm->getText("RendererManager.cull_front_and_back"); break;

		default : break;
	}
}

void RendererManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
	if(ImGui::Begin(std::string(AKS_ICON_MD_TV" " + _eltm->getText("RendererManager.name")).c_str(), nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		render_sets();
		render_stats();
		ImGui::End();
	}
}

void RendererManager::render_sets()
{
	if(ImGui::TreeNodeEx(std::string(AKS_ICON_MD_DISPLAY_SETTINGS" " + _eltm->getText("RendererManager.render_sets")).c_str(), ImGuiTreeNodeFlags_Framed))
	{
		ImGui::Text(_eltm->getText("RendererManager.culling").c_str());
		ImGui::SameLine();
		if(ImGui::BeginCombo("##combo", selected.c_str()))
		{
			int item_current_idx = Ak::getMainAppProjectFile().archive()["cullmode"];
			if(ImGui::Selectable(_eltm->getText("RendererManager.cull_none").c_str(), item_current_idx == VK_CULL_MODE_NONE))
			{
				item_current_idx = VK_CULL_MODE_NONE;
				selected = _eltm->getText("RendererManager.cull_none");
			}
			if(ImGui::Selectable(_eltm->getText("RendererManager.cull_front").c_str(), item_current_idx == VK_CULL_MODE_FRONT_BIT))
			{
				item_current_idx = VK_CULL_MODE_FRONT_BIT;
				selected = _eltm->getText("RendererManager.cull_front");
			}
			if(ImGui::Selectable(_eltm->getText("RendererManager.cull_back").c_str(), item_current_idx == VK_CULL_MODE_BACK_BIT))
			{
				item_current_idx = VK_CULL_MODE_BACK_BIT;
				selected = _eltm->getText("RendererManager.cull_back");
			}
			if(ImGui::Selectable(_eltm->getText("RendererManager.cull_front_and_back").c_str(), item_current_idx == VK_CULL_MODE_FRONT_AND_BACK))
			{
				item_current_idx = VK_CULL_MODE_FRONT_AND_BACK;
				selected = _eltm->getText("RendererManager.cull_front_and_back");
			}
			ImGui::EndCombo();

			if(item_current_idx != Ak::getMainAppProjectFile().archive()["cullmode"])
			{
				Ak::getMainAppProjectFile().archive()["cullmode"] = item_current_idx;
				//Ak::RendererComponent* renderer = static_cast<Ak::RendererComponent*>(Ak::getMainAppComponentStack()->get_component("__renderer_component"));
				//renderer->setCullMode(item_current_idx);
				//renderer->reloadRenderer();
			}
		}

		Ak::RendererComponent* renderer = static_cast<Ak::RendererComponent*>(Ak::getMainAppComponentStack()->get_component("__renderer_component0"));
		//static ImVec4 color = ImVec4(renderer->getClearValue().color.float32[0], renderer->getClearValue().color.float32[1], renderer->getClearValue().color.float32[2], renderer->getClearValue().color.float32[3]);
		static ImVec4 color = ImVec4(0.f, 0.f, 0.f, 1.f);
		ImGui::ColorEdit4("##picker", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
		/*
		renderer->getClearValue().color.float32[0] = color.x;
		renderer->getClearValue().color.float32[1] = color.y;
		renderer->getClearValue().color.float32[2] = color.z;
		*/
		ImGui::SameLine();
		ImGui::Text(_eltm->getText("RendererManager.bg_color").c_str());

		if(ImGui::Button(std::string(AKS_ICON_MD_REFRESH" " + _eltm->getText("RendererManager.reload")).c_str()))
			Ak::EventBus::send("__renderer_component0", Ak::ResizeEvent{});

		bool vsync_save = renderer->getWindow()->vsync;
		ImGui::Checkbox("Vsync", &renderer->getWindow()->vsync);
		if(vsync_save != renderer->getWindow()->vsync)
			renderer->getWindow()->fetchSettings();

		ImGui::TreePop();
	}
}

void RendererManager::render_stats()
{
	if(ImGui::TreeNodeEx(std::string(AKS_ICON_MD_QUERY_STATS" " + _eltm->getText("RendererManager.stats")).c_str(), ImGuiTreeNodeFlags_Framed))
	{
		ImGui::Text(_eltm->getText("RendererManager.vulkan_v").c_str(), _gpu.getVulkanVersion().c_str());
		ImGui::Text(_eltm->getText("RendererManager.n_devices").c_str(), _gpu.getNumberOfDevices());
		ImGui::Separator();
		ImGui::Text(_eltm->getText("RendererManager.model").c_str(), _gpu.getModelName().c_str());
		ImGui::Text(_eltm->getText("RendererManager.vendor").c_str(), _gpu.getVendorName().c_str());
		ImGui::Text(_eltm->getText("RendererManager.model_type").c_str(), _gpu.getDeviceType().c_str());
		ImGui::TreePop();
	}
}
