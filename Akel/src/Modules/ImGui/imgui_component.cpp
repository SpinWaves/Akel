// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/07/2021
// Updated : 31/05/2022

#include <Modules/ImGui/imgui.h>
#include <Core/core.h>
#include <Platform/messageBox.h>
#include <Renderer/Core/render_core.h>
#include <Platform/window.h>

namespace Ak
{
	static ImVec4 clear_color = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	VkDescriptorPool descriptorPool = VK_NULL_HANDLE;

	ImGuiComponent::ImGuiComponent() : Component("__imguiComponent") {}

	void ImGuiComponent::onAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

		if(_settingsFilePath != nullptr)		
		{
			io.IniFilename = _settingsFilePath;
			ImGui::LoadIniSettingsFromDisk(_settingsFilePath);
			ImGui::SaveIniSettingsToDisk(_settingsFilePath);
		}

		io.Fonts->AddFontFromFileTTF(std::string(Core::getFontsDirPath() + "opensans/OpenSans-Bold.ttf").c_str(), 19.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF(std::string(Core::getFontsDirPath() + "opensans/OpenSans-Regular.ttf").c_str(), 19.0f);

		SetDarkThemeColors();

		if(descriptorPool == VK_NULL_HANDLE)
		{
			VkDescriptorPoolSize pool_sizes[] =
			{
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
		ImGui_ImplSDL2_InitForVulkan(Render_Core::get().getWindow()->getNativeWindow());
		ImGui_ImplVulkan_InitInfo init_info{};
			init_info.Instance = Render_Core::get().getInstance().get();
			init_info.PhysicalDevice = Render_Core::get().getDevice().getPhysicalDevice();
			init_info.Device = Render_Core::get().getDevice().get();
			init_info.QueueFamily = *Render_Core::get().getQueue().getFamilies().graphicsFamily;
			init_info.Queue = Render_Core::get().getQueue().getGraphic();
			init_info.DescriptorPool = descriptorPool;
			init_info.Allocator = nullptr;
			init_info.MinImageCount = Render_Core::get().getSwapChain().getSupport().capabilities.minImageCount;
			init_info.ImageCount = Render_Core::get().getSwapChain().getSupport().capabilities.maxImageCount;
			init_info.CheckVkResultFn = RCore::checkVk;
		ImGui_ImplVulkan_Init(&init_info, Render_Core::get().getRenderPass().get());

		{
			Render_Core::get().getActiveCmdBuffer().beginRecord(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
			ImGui_ImplVulkan_CreateFontsTexture(Render_Core::get().getActiveCmdBuffer().get());
			Render_Core::get().getActiveCmdBuffer().endRecord();

			vkDeviceWaitIdle(Render_Core::get().getDevice().get());
			ImGui_ImplVulkan_DestroyFontUploadObjects();
		}

		_componentsInit++;
	}

	void ImGuiComponent::begin()
	{
		if(Render_Core::get().isFrameBufferResizeRequested() && Render_Core::get().getWindow() != nullptr)
			ImGui_ImplVulkan_SetMinImageCount(Render_Core::get().getSwapChain().getSupport().capabilities.minImageCount);
        // Start the Dear ImGui frame
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
	}

	void ImGuiComponent::end()
	{
		// Rendering
        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        if(!(draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f))
			ImGui_ImplVulkan_RenderDrawData(draw_data, Render_Core::get().getActiveCmdBuffer().get());
	}

	void ImGuiComponent::onImGuiEvent(Input& input)
	{
		ImGui_ImplSDL2_ProcessEvent(input.getNativeEvent());
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

		colors[ImGuiCol_Text]                   = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_TextDisabled]           = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
		colors[ImGuiCol_WindowBg]               = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		colors[ImGuiCol_ChildBg]                = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
		colors[ImGuiCol_PopupBg]                = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_Border]                 = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
		colors[ImGuiCol_BorderShadow]           = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
		colors[ImGuiCol_FrameBg]                = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
		colors[ImGuiCol_FrameBgActive]          = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
		colors[ImGuiCol_TitleBg]                = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgActive]          = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_MenuBarBg]              = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_CheckMark]              = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_SliderGrab]             = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Button]                 = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
		colors[ImGuiCol_ButtonHovered]          = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_ButtonActive]           = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
		colors[ImGuiCol_Header]                 = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_HeaderHovered]          = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_HeaderActive]           = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_Separator]              = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SeparatorActive]        = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_ResizeGrip]             = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
		colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
		colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Tab]                    = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabHovered]             = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
		colors[ImGuiCol_TabActive]              = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_TabUnfocused]           = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_PlotLines]              = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_PlotHistogram]          = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
		colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_DragDropTarget]         = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavHighlight]           = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
		colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
		colors[ImGuiCol_DockingPreview]         = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
		colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 1.0f;
		style->TabRounding = 0.0f;
		style->WindowRounding = 4.0f;
	}
}
