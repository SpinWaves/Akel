// This file is a part of AtlasEngine
// CREATED : 10/04/2021
// UPDATED : 05/06/2021

#ifndef __AE_INSTANCE__
#define __AE_INSTANCE__

#include <AEpch.h>

namespace AE
{

    #define VK_FORMAT_RGBA_8_SRGB VK_FORMAT_B8G8R8A8_SRGB
    const int MAX_FRAMES_IN_FLIGHT = 2;

    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

    const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    #ifdef DEBUG
        constexpr bool enableValidationLayers = true;
    #else
        constexpr bool enableValidationLayers = false;
    #endif

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class Instance
    {
        public:
            void init(SDL_Window* win, const char* vertexShader, const char* fragmentShader);
            void render();

            ~Instance();

        protected:
            void cleanup();

        private:
            void createInstance();

            // Device
            void pickPhysicalDevice();
            bool isDeviceSuitable(VkPhysicalDevice device);

            // Validation layers
            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
            void setupDebugMessenger(); 

            bool checkValidationLayerSupport();
            std::vector<const char*> getRequiredExtensions();

            static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

            VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);

            void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);

            // Queue
            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

            // Logical device
            void createLogicalDevice();

            // Vk surface
            void createSurface();
            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

            // Swap chain
            void createSwapChain();
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

            // Image views
            void createImageViews();

            // Pipeline graphique
            void createGraphicsPipeline();
            static std::vector<char> readFile(const std::string& filename);
            VkShaderModule createShaderModule(const std::vector<char>& code);

            // Render pass
            void createRenderPass();

            // FrameBuffer
            void createFramebuffers();

            // Command buffer
            void createCommandPool();
            void createCommandBuffers();

            // Rendering
            void createSemaphores();

            // =============================================================== //

            VkInstance instance;
            VkDebugUtilsMessengerEXT debugMessenger;
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkDevice device;

            // Queues
            VkQueue graphicsQueue;
            VkQueue presentQueue;

            // Vk surface
            VkSurfaceKHR surface;

            // Swap chain
            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;
            std::vector<VkFramebuffer> swapChainFramebuffers;

            // Image views
            std::vector<VkImageView> swapChainImageViews;

            // Pipeline graphique
            VkPipelineLayout pipelineLayout;
            VkPipeline graphicsPipeline;

            // Render pass
            VkRenderPass renderPass;

            // Command buffer
            VkCommandPool commandPool;
            std::vector<VkCommandBuffer> commandBuffers;

            // Rendering
            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;
            std::vector<VkFence> imagesInFlight;
            size_t currentFrame = 0;

            const char* vertShader;
            const char* fragShader;

            SDL_Window* window;
    };
}

#endif // __AE_INSTANCE__
