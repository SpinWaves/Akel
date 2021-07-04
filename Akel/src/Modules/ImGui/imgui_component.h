// This file is a part of Akel
// CREATED : 03/07/2021
// UPDATED : 04/07/2021

#ifndef __AK_IMGUI_COMPONENT__
#define __AK_IMGUI_COMPONENT__

#include <Akpch.h>
#include <Core/Components/baseComponent.h>
#include <Platform/window.h>

namespace Ak
{
	class ImGuiComponent : public Component
	{
		public:
			ImGuiComponent();

			virtual void onAttach() override;
			virtual void update() override;
			virtual void onEvent(Input& input) override;
			virtual void onQuit() override;

			void begin();
			void end();

			~ImGuiComponent() = default;

		private:
			void SetDarkThemeColors();
			VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData);

			void SetupVulkan(const char** extensions, uint32_t extensions_count);
			void SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height);
			void CleanupVulkanWindow();
			void CleanupVulkan();
			void FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data);
			void FramePresent(ImGui_ImplVulkanH_Window* wd);

			SDL_Window* window;
			VkResult err;
			ImGui_ImplVulkanH_Window* wd;
			ImGuiIO& io = ImGui::GetIO();

			VkAllocationCallbacks*   g_Allocator = NULL;
			VkInstance               g_Instance = VK_NULL_HANDLE;
			VkPhysicalDevice         g_PhysicalDevice = VK_NULL_HANDLE;
			VkDevice                 g_Device = VK_NULL_HANDLE;
			uint32_t                 g_QueueFamily = (uint32_t)-1;
			VkQueue                  g_Queue = VK_NULL_HANDLE;
			VkDebugReportCallbackEXT g_DebugReport = VK_NULL_HANDLE;
			VkPipelineCache          g_PipelineCache = VK_NULL_HANDLE;
			VkDescriptorPool         g_DescriptorPool = VK_NULL_HANDLE;

			ImGui_ImplVulkanH_Window g_MainWindowData;
			uint32_t                 g_MinImageCount = 2;
			bool                     g_SwapChainRebuild = false;
			int                      g_SwapChainResizeWidth = 0;
			int                      g_SwapChainResizeHeight = 0;


			bool show_demo_window = true;
			bool show_another_window = false;
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	};
}

#endif // __AK_IMGUI_COMPONENT__

