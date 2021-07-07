// This file is a part of Akel
// CREATED : 03/07/2021
// UPDATED : 07/07/2021

#include <Modules/ImGui/imgui.h>
#include <Core/core.h>
#include <Platform/messageBox.h>

namespace Ak
{
	static void check_vk_result(VkResult err);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData);
	static void SetupVulkan(const char** extensions, uint32_t extensions_count);
	static void SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height);
	static void CleanupVulkanWindow();
	static void CleanupVulkan();
	static void FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data);
	static void FramePresent(ImGui_ImplVulkanH_Window* wd);


	static VkResult err;

	static VkAllocationCallbacks*   g_Allocator = NULL;
	static VkInstance               g_Instance = VK_NULL_HANDLE;
	static VkPhysicalDevice         g_PhysicalDevice = VK_NULL_HANDLE;
	static VkDevice                 g_Device = VK_NULL_HANDLE;
	static uint32_t                 g_QueueFamily = (uint32_t)-1;
	static VkQueue                  g_Queue = VK_NULL_HANDLE;
	static VkDebugReportCallbackEXT g_DebugReport = VK_NULL_HANDLE;
	static VkPipelineCache          g_PipelineCache = VK_NULL_HANDLE;
	static VkDescriptorPool         g_DescriptorPool = VK_NULL_HANDLE;

	static ImGui_ImplVulkanH_Window g_MainWindowData;
	static uint32_t                 g_MinImageCount = 2;
	static bool                     g_SwapChainRebuild = false;
	static int                      g_SwapChainResizeWidth = 0;
	static int                      g_SwapChainResizeHeight = 0;

	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	static ImGui_ImplVulkanH_Window* _wd = &g_MainWindowData;

	ImGuiComponent::ImGuiComponent(const char* title) : Window()
	{
		_title = title;
	}

	void ImGuiComponent::onAttach()
	{
		Window::create();
		Window::setSetting<title>(_title);
		Window::setSetting<resizable>(true);
		Window::setSetting<dimensions>(AK_WINDOW_MAX_SIZE, AK_WINDOW_MAX_SIZE);
		//Window::setSetting<position>(0, 0);

		// Setup Vulkan
		uint32_t extensions_count = 0;
		SDL_Vulkan_GetInstanceExtensions(_window, &extensions_count, NULL);
		const char** extensions = new const char*[extensions_count];
		SDL_Vulkan_GetInstanceExtensions(_window, &extensions_count, extensions);
		SetupVulkan(extensions, extensions_count);
		delete[] extensions;

		// Create Window Surface
		VkSurfaceKHR surface;
		VkResult err;
		if(SDL_Vulkan_CreateSurface(_window, g_Instance, &surface) == 0)
			messageBox(FATAL_ERROR, "Unable to create ImGui window", "Failed to create Vulkan surface");

		// Create Framebuffers
		int w, h;
		SDL_GetWindowSize(_window, &w, &h);
		SetupVulkanWindow(_wd, surface, w, h);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

		io.Fonts->AddFontFromFileTTF(std::string(Core::getAssetsDirPath() + "fonts/opensans/OpenSans-Bold.ttf").c_str(), 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF(std::string(Core::getAssetsDirPath() + "fonts/opensans/OpenSans-Regular.ttf").c_str(), 18.0f);

		SetDarkThemeColors();

		// Setup Platform/Renderer bindings
		ImGui_ImplSDL2_InitForVulkan(_window);
		ImGui_ImplVulkan_InitInfo init_info = {};
			init_info.Instance = g_Instance;
			init_info.PhysicalDevice = g_PhysicalDevice;
			init_info.Device = g_Device;
			init_info.QueueFamily = g_QueueFamily;
			init_info.Queue = g_Queue;
			init_info.PipelineCache = g_PipelineCache;
			init_info.DescriptorPool = g_DescriptorPool;
			init_info.Allocator = g_Allocator;
			init_info.MinImageCount = g_MinImageCount;
			init_info.ImageCount = _wd->ImageCount;
			init_info.CheckVkResultFn = check_vk_result;
		ImGui_ImplVulkan_Init(&init_info, _wd->RenderPass);

		{
			// Use any command queue
			VkCommandPool command_pool = _wd->Frames[_wd->FrameIndex].CommandPool;
			VkCommandBuffer command_buffer = _wd->Frames[_wd->FrameIndex].CommandBuffer;

			err = vkResetCommandPool(g_Device, command_pool, 0);
			check_vk_result(err);
			VkCommandBufferBeginInfo begin_info = {};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			err = vkBeginCommandBuffer(command_buffer, &begin_info);
			check_vk_result(err);

			ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

			VkSubmitInfo end_info = {};
			end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			end_info.commandBufferCount = 1;
			end_info.pCommandBuffers = &command_buffer;
			err = vkEndCommandBuffer(command_buffer);
			check_vk_result(err);
			err = vkQueueSubmit(g_Queue, 1, &end_info, VK_NULL_HANDLE);
			check_vk_result(err);

			err = vkDeviceWaitIdle(g_Device);
			check_vk_result(err);
			ImGui_ImplVulkan_DestroyFontUploadObjects();
		}
	}
	
	void ImGuiComponent::begin()
	{
		if(g_SwapChainRebuild)
        {
            int width, height;
            SDL_GetWindowSize(_window, &width, &height);
            if(width > 0 && height > 0)
            {
                ImGui_ImplVulkan_SetMinImageCount(g_MinImageCount);
                ImGui_ImplVulkanH_CreateOrResizeWindow(g_Instance, g_PhysicalDevice, g_Device, &g_MainWindowData, g_QueueFamily, g_Allocator, width, height, g_MinImageCount);
                g_MainWindowData.FrameIndex = 0;
                g_SwapChainRebuild = false;
            }
        }
        // Start the Dear ImGui frame
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplSDL2_NewFrame(_window);
        ImGui::NewFrame();
	}

	void ImGuiComponent::end()
	{
		// Rendering
        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
        if(!is_minimized)
        {
            _wd->ClearValue.color.float32[0] = clear_color.x * clear_color.w;
            _wd->ClearValue.color.float32[1] = clear_color.y * clear_color.w;
            _wd->ClearValue.color.float32[2] = clear_color.z * clear_color.w;
            _wd->ClearValue.color.float32[3] = clear_color.w;
            FrameRender(_wd, draw_data);
            FramePresent(_wd);
        }
	}

	void ImGuiComponent::onEvent(Input& input)
	{
		ImGui_ImplSDL2_ProcessEvent(input.getNativeEvent());
	}
	void ImGuiComponent::onQuit()
	{
		err = vkDeviceWaitIdle(g_Device);
		check_vk_result(err);
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		CleanupVulkanWindow();
		CleanupVulkan();

		SDL_DestroyWindow(_window);
	}

	void ImGuiComponent::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

	static void check_vk_result(VkResult err)
	{
		if(err == 0)
			return;
		Core::log::report(ERROR, std::string("Imgui: Vulkan: VkResult = " + err));
		if(err < 0)
			abort();
	}

#ifdef IMGUI_VULKAN_DEBUG_REPORT
	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
	{
		(void)flags; (void)object; (void)location; (void)messageCode; (void)pUserData; (void)pLayerPrefix; // Unused arguments
		Core::log::report(ERROR, std::string("ImGui: Vulkan: debug report from ObjectType: " + objectType + "\nMessage:" + pMessage));
		return VK_FALSE;
	}
#endif // IMGUI_VULKAN_DEBUG_REPORT

	static void SetupVulkan(const char** extensions, uint32_t extensions_count)
	{
		VkResult err;

		// Create Vulkan Instance
		{
			VkInstanceCreateInfo create_info = {};
			create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			create_info.enabledExtensionCount = extensions_count;
			create_info.ppEnabledExtensionNames = extensions;
#ifdef IMGUI_VULKAN_DEBUG_REPORT
			// Enabling validation layers
			const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
			create_info.enabledLayerCount = 1;
			create_info.ppEnabledLayerNames = layers;

			// Enable debug report extension (we need additional storage, so we duplicate the user array to add our new extension to it)
			const char** extensions_ext = (const char**)malloc(sizeof(const char*) * (extensions_count + 1));
			memcpy(extensions_ext, extensions, extensions_count * sizeof(const char*));
			extensions_ext[extensions_count] = "VK_EXT_debug_report";
			create_info.enabledExtensionCount = extensions_count + 1;
			create_info.ppEnabledExtensionNames = extensions_ext;

			// Create Vulkan Instance
			err = vkCreateInstance(&create_info, g_Allocator, &g_Instance);
			check_vk_result(err);
			free(extensions_ext);

			// Get the function pointer (required for any extensions)
			auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(g_Instance, "vkCreateDebugReportCallbackEXT");
			IM_ASSERT(vkCreateDebugReportCallbackEXT != NULL);

			// Setup the debug report callback
			VkDebugReportCallbackCreateInfoEXT debug_report_ci = {};
			debug_report_ci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			debug_report_ci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
			debug_report_ci.pfnCallback = debug_report;
			debug_report_ci.pUserData = NULL;
			err = vkCreateDebugReportCallbackEXT(g_Instance, &debug_report_ci, g_Allocator, &g_DebugReport);
			check_vk_result(err);
#else
			// Create Vulkan Instance without any debug feature
			err = vkCreateInstance(&create_info, g_Allocator, &g_Instance);
			check_vk_result(err);
			IM_UNUSED(g_DebugReport);
#endif
		}

		// Select GPU
		{
			uint32_t gpu_count;
			err = vkEnumeratePhysicalDevices(g_Instance, &gpu_count, NULL);
			check_vk_result(err);
			IM_ASSERT(gpu_count > 0);

			VkPhysicalDevice* gpus = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpu_count);
			err = vkEnumeratePhysicalDevices(g_Instance, &gpu_count, gpus);
			check_vk_result(err);

			// If a number >1 of GPUs got reported, find discrete GPU if present, or use first one available. This covers
			// most common cases (multi-gpu/integrated+dedicated graphics). Handling more complicated setups (multiple
			// dedicated GPUs) is out of scope of this sample.
			int use_gpu = 0;
			for (int i = 0; i < (int)gpu_count; i++)
			{
				VkPhysicalDeviceProperties properties;
				vkGetPhysicalDeviceProperties(gpus[i], &properties);
				if(properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				{
					use_gpu = i;
					break;
				}
			}

			g_PhysicalDevice = gpus[use_gpu];
			free(gpus);
		}

		// Select graphics queue family
		{
			uint32_t count;
			vkGetPhysicalDeviceQueueFamilyProperties(g_PhysicalDevice, &count, NULL);
			VkQueueFamilyProperties* queues = (VkQueueFamilyProperties*)malloc(sizeof(VkQueueFamilyProperties) * count);
			vkGetPhysicalDeviceQueueFamilyProperties(g_PhysicalDevice, &count, queues);
			for (uint32_t i = 0; i < count; i++)
				if(queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					g_QueueFamily = i;
					break;
				}
			free(queues);
			IM_ASSERT(g_QueueFamily != (uint32_t)-1);
		}

		// Create Logical Device (with 1 queue)
		{
			int device_extension_count = 1;
			const char* device_extensions[] = { "VK_KHR_swapchain" };
			const float queue_priority[] = { 1.0f };
			VkDeviceQueueCreateInfo queue_info[1] = {};
			queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queue_info[0].queueFamilyIndex = g_QueueFamily;
			queue_info[0].queueCount = 1;
			queue_info[0].pQueuePriorities = queue_priority;
			VkDeviceCreateInfo create_info = {};
			create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			create_info.queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]);
			create_info.pQueueCreateInfos = queue_info;
			create_info.enabledExtensionCount = device_extension_count;
			create_info.ppEnabledExtensionNames = device_extensions;
			err = vkCreateDevice(g_PhysicalDevice, &create_info, g_Allocator, &g_Device);
			check_vk_result(err);
			vkGetDeviceQueue(g_Device, g_QueueFamily, 0, &g_Queue);
		}

		// Create Descriptor Pool
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
			pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
			pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
			pool_info.pPoolSizes = pool_sizes;
			err = vkCreateDescriptorPool(g_Device, &pool_info, g_Allocator, &g_DescriptorPool);
			check_vk_result(err);
		}
	}

	// All the ImGui_ImplVulkanH_XXX structures/functions are optional helpers used by the demo.
	// Your real engine/app may not use them.
	static void SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height)
	{
		wd->Surface = surface;

		// Check for WSI support
		VkBool32 res;
		vkGetPhysicalDeviceSurfaceSupportKHR(g_PhysicalDevice, g_QueueFamily, wd->Surface, &res);
		if(res != VK_TRUE)
			messageBox(FATAL_ERROR, "Vulkan error for ImGui window", "Error no WSI support on physical device 0");

		// Select Surface Format
		const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
		const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
		wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(g_PhysicalDevice, wd->Surface, requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

		// Select Present Mode
#ifdef IMGUI_UNLIMITED_FRAME_RATE
		VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR };
#else
		VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_FIFO_KHR };
#endif
		wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(g_PhysicalDevice, wd->Surface, &present_modes[0], IM_ARRAYSIZE(present_modes));
		//printf("[vulkan] Selected PresentMode = %d\n", wd->PresentMode);

		// Create SwapChain, RenderPass, Framebuffer, etc.
		IM_ASSERT(g_MinImageCount >= 2);
		ImGui_ImplVulkanH_CreateOrResizeWindow(g_Instance, g_PhysicalDevice, g_Device, wd, g_QueueFamily, g_Allocator, width, height, g_MinImageCount);
	}

	static void CleanupVulkan()
	{
		vkDestroyDescriptorPool(g_Device, g_DescriptorPool, g_Allocator);

#ifdef IMGUI_VULKAN_DEBUG_REPORT
		// Remove the debug report callback
		auto vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(g_Instance, "vkDestroyDebugReportCallbackEXT");
		vkDestroyDebugReportCallbackEXT(g_Instance, g_DebugReport, g_Allocator);
#endif // IMGUI_VULKAN_DEBUG_REPORT

		vkDestroyDevice(g_Device, g_Allocator);
		vkDestroyInstance(g_Instance, g_Allocator);
	}

	static void CleanupVulkanWindow()
	{
		ImGui_ImplVulkanH_DestroyWindow(g_Instance, g_Device, &g_MainWindowData, g_Allocator);
	}

	static void FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data)
	{
		VkResult err;

		VkSemaphore image_acquired_semaphore  = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
		VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
		err = vkAcquireNextImageKHR(g_Device, wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &wd->FrameIndex);
		if(err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
		{
			g_SwapChainRebuild = true;
			return;
		}
		check_vk_result(err);

		ImGui_ImplVulkanH_Frame* fd = &wd->Frames[wd->FrameIndex];
		{
			err = vkWaitForFences(g_Device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking
			check_vk_result(err);

			err = vkResetFences(g_Device, 1, &fd->Fence);
			check_vk_result(err);
		}
		{
			err = vkResetCommandPool(g_Device, fd->CommandPool, 0);
			check_vk_result(err);
			VkCommandBufferBeginInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
			check_vk_result(err);
		}
		{
			VkRenderPassBeginInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			info.renderPass = wd->RenderPass;
			info.framebuffer = fd->Framebuffer;
			info.renderArea.extent.width = wd->Width;
			info.renderArea.extent.height = wd->Height;
			info.clearValueCount = 1;
			info.pClearValues = &wd->ClearValue;
			vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
		}

		// Record dear imgui primitives into command buffer
		ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);

		// Submit command buffer
		vkCmdEndRenderPass(fd->CommandBuffer);
		{
			VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			VkSubmitInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			info.waitSemaphoreCount = 1;
			info.pWaitSemaphores = &image_acquired_semaphore;
			info.pWaitDstStageMask = &wait_stage;
			info.commandBufferCount = 1;
			info.pCommandBuffers = &fd->CommandBuffer;
			info.signalSemaphoreCount = 1;
			info.pSignalSemaphores = &render_complete_semaphore;

			err = vkEndCommandBuffer(fd->CommandBuffer);
			check_vk_result(err);
			err = vkQueueSubmit(g_Queue, 1, &info, fd->Fence);
			check_vk_result(err);
		}
	}

	static void FramePresent(ImGui_ImplVulkanH_Window* wd)
	{
		if(g_SwapChainRebuild)
			return;
		VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
		VkPresentInfoKHR info = {};
		info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		info.waitSemaphoreCount = 1;
		info.pWaitSemaphores = &render_complete_semaphore;
		info.swapchainCount = 1;
		info.pSwapchains = &wd->Swapchain;
		info.pImageIndices = &wd->FrameIndex;
		VkResult err = vkQueuePresentKHR(g_Queue, &info);
		if(err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
		{
			g_SwapChainRebuild = true;
			return;
		}
		check_vk_result(err);
		wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->ImageCount; // Now we can use the next set of semaphores
	}
}

