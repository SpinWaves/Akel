// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/07/2021
// Updated : 19/01/2023

#include <Modules/ImGui/imgui.h>
#include <Core/core.h>
#include <Platform/messageBox.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	static VkDescriptorPool descriptorPool = VK_NULL_HANDLE;

	ImGuiComponent::ImGuiComponent(RendererComponent* renderer) : Component("__imgui_component"), _renderer(renderer) {}

	void ImGuiComponent::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking

		if(_settingsFilePath != "imgui.ini")
		{
			io.IniFilename = _settingsFilePath.c_str();
			ImGui::LoadIniSettingsFromDisk(_settingsFilePath.c_str());
			ImGui::SaveIniSettingsToDisk(_settingsFilePath.c_str());
		}

		SetDarkThemeColors();

		if(descriptorPool == VK_NULL_HANDLE)
		{
			VkDescriptorPoolSize pool_sizes[] = {
				{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
				{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
				{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
				{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
			};

			VkDescriptorPoolCreateInfo pool_info = {};
			pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
			pool_info.maxSets = 1000 * ARRAY_SIZE(pool_sizes);
			pool_info.poolSizeCount = (uint32_t)ARRAY_SIZE(pool_sizes);
			pool_info.pPoolSizes = pool_sizes;
			RCore::checkVk(vkCreateDescriptorPool(Render_Core::get().getDevice().get(), &pool_info, nullptr, &descriptorPool));
		}

		// Setup Platform/Renderer bindings
		ImGui_ImplVulkan_LoadFunctions([](const char *function_name, void *vulkan_instance) {
			return vkGetInstanceProcAddr(*(reinterpret_cast<VkInstance *>(vulkan_instance)), function_name);
		}, &Render_Core::get().getInstance().get());

		ImGui_ImplSDL2_InitForVulkan(_renderer->getWindow()->getNativeWindow());
		ImGui_ImplVulkan_InitInfo init_info{};
			init_info.Instance = Render_Core::get().getInstance().get();
			init_info.PhysicalDevice = Render_Core::get().getDevice().getPhysicalDevice();
			init_info.Device = Render_Core::get().getDevice().get();
			init_info.QueueFamily = *Render_Core::get().getQueue().getFamilies().graphicsFamily;
			init_info.Queue = Render_Core::get().getQueue().getGraphic();
			init_info.DescriptorPool = descriptorPool;
			init_info.Allocator = nullptr;
			init_info.MinImageCount = _renderer->getSwapChain().getSupport().capabilities.minImageCount;
			init_info.ImageCount = _renderer->getSwapChain().getImagesNumber();
			init_info.CheckVkResultFn = RCore::checkVk;
		ImGui_ImplVulkan_Init(&init_info, _renderer->getRenderPass().get());

		_componentsInit = true;
	}

	void ImGuiComponent::generateFonts()
	{
		_renderer->getActiveCmdBuffer().beginRecord(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

			ImGui_ImplVulkan_CreateFontsTexture(_renderer->getActiveCmdBuffer().get());

			VkSubmitInfo end_info{};
			end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			end_info.commandBufferCount = 1;
			end_info.pCommandBuffers = &_renderer->getActiveCmdBuffer().get();

		_renderer->getActiveCmdBuffer().endRecord();

		if(vkQueueSubmit(Render_Core::get().getQueue().getGraphic(), 1, &end_info, VK_NULL_HANDLE) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Imgui Vulkan error : failed to submit font command buffer");

		vkDeviceWaitIdle(Render_Core::get().getDevice().get());
		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	void ImGuiComponent::onImGuiEvent(Input& input)
	{
		ImGui_ImplSDL2_ProcessEvent(input.getNativeEvent());
	}

	void ImGuiComponent::addFontFromFile(const char* file, float size, bool def)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF(file, size);
		if(def)
			io.FontDefault = io.Fonts->AddFontFromFileTTF(file, size);

		_renderer->getActiveCmdBuffer().beginRecord(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
			ImGui_ImplVulkan_CreateFontsTexture(_renderer->getActiveCmdBuffer().get());
			VkSubmitInfo end_info{};
			end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			end_info.commandBufferCount = 1;
			end_info.pCommandBuffers = &_renderer->getActiveCmdBuffer().get();
		_renderer->getActiveCmdBuffer().endRecord();
		
		if(vkQueueSubmit(Render_Core::get().getQueue().getGraphic(), 1, &end_info, VK_NULL_HANDLE) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Imgui Vulkan error : failed to submit font command buffer");

		vkDeviceWaitIdle(Render_Core::get().getDevice().get());
		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	void ImGuiComponent::addFontFromRawTTF(uint32_t* data, size_t data_size, ImFontConfig conf, ImWchar* range, float size, bool def)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromMemoryCompressedTTF(data, data_size, size, &conf, range);
		if(def)
			io.FontDefault = io.Fonts->AddFontFromMemoryCompressedTTF(data, data_size, size, &conf, range);

		_renderer->getActiveCmdBuffer().beginRecord(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
			ImGui_ImplVulkan_CreateFontsTexture(_renderer->getActiveCmdBuffer().get());
			VkSubmitInfo end_info{};
			end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			end_info.commandBufferCount = 1;
			end_info.pCommandBuffers = &_renderer->getActiveCmdBuffer().get();
		_renderer->getActiveCmdBuffer().endRecord();

		if(vkQueueSubmit(Render_Core::get().getQueue().getGraphic(), 1, &end_info, VK_NULL_HANDLE) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Imgui Vulkan error : failed to submit font command buffer");

		vkDeviceWaitIdle(Render_Core::get().getDevice().get());
		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	void ImGuiComponent::renderFrame()
	{
		ImDrawData* draw_data = ImGui::GetDrawData();
		if(draw_data->DisplaySize.x >= 0.0f && draw_data->DisplaySize.y >= 0.0f)
			ImGui_ImplVulkan_RenderDrawData(draw_data, _renderer->getActiveCmdBuffer().get());
	}

	void ImGuiComponent::onQuit()
	{
		vkDeviceWaitIdle(Render_Core::get().getDevice().get());
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		vkDestroyDescriptorPool(Render_Core::get().getDevice().get(), descriptorPool, nullptr);
	}

	void ImGuiComponent::SetDarkThemeColors()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		ImGui::StyleColorsDark();
		colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg]              = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ChildBg]               = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
		colors[ImGuiCol_PopupBg]               = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		colors[ImGuiCol_Border]                = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		colors[ImGuiCol_BorderShadow]          = ImVec4(0.05f, 0.05f, 0.05f, 0.24f);
		colors[ImGuiCol_FrameBg]               = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgActive]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg]               = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		colors[ImGuiCol_TitleBgActive]         = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		colors[ImGuiCol_MenuBarBg]             = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark]             = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_SliderGrab]            = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_ButtonActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_Header]                = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_HeaderHovered]         = ImVec4(0.05f, 0.05f, 0.05f, 0.36f);
		colors[ImGuiCol_HeaderActive]          = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator]             = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip]            = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_Tab]                   = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_TabHovered]            = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive]             = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_TabUnfocused]          = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_DockingPreview]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_DockingEmptyBg]        = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.05f, 0.05f, 0.05f, 0.52f);
		colors[ImGuiCol_TableBorderLight]      = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_TableRowBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt]         = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 0.0f;
		style->TabRounding = 5.0f;
		style->WindowRounding = 0.0f;
		style->WindowBorderSize = 1.0f;
		style->AntiAliasedLines = true;
		style->AntiAliasedFill = true;
		style->TabBorderSize = 2.0f;
	}
}
