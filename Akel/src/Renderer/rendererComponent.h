// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 02/03/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>

namespace Ak
{
    constexpr const int MAX_FRAMES_IN_FLIGHT = 2;

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        inline bool isComplete()
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

    struct Vertex
    {
        glm::vec2 pos;
        glm::vec3 color;

        static VkVertexInputBindingDescription getBindingDescription()
        {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
        {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            return attributeDescriptions;
        }
    };

    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

    #ifdef AK_DEBUG
        constexpr const bool enableValidationLayers = true;
    #else
        constexpr const bool enableValidationLayers = false;
    #endif

    class RendererComponent : public Component
    {
        public:
            RendererComponent(SDL_Window* win);
            RendererComponent();

            void onAttach() override;
            void onRender() override;
            void onQuit() override;

            inline void setShader(std::string vertexShader, std::string fragmentShader) { _vertexShader = std::move(vertexShader); _fragmentShader = std::move(fragmentShader); }
            inline void render_to_window(SDL_Window* win) noexcept { window = win; }

            ~RendererComponent() = default;

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
            void cleanupSwapChain();

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
            void drawFrame();
            void createSemaphores();

            // VertexBuffer
            void createVertexBuffer();
            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
            void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
            void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
            void createIndexBuffer();

            std::string _vertexShader = Core::getMainDirPath() + "Akel/src/Shaders/basic_2D/basic_2D.vert.spv";
            std::string _fragmentShader = Core::getMainDirPath() + "Akel/src/Shaders/basic_2D/basic_2D.frag.spv";

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

            // Vertex Buffer
            VkBuffer vertexBuffer;
            VkDeviceMemory vertexBufferMemory;
            VkBuffer indexBuffer;
            VkDeviceMemory indexBufferMemory;

            SDL_Window* window;

            bool _instanceInitialized = false;

            
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;
    };
}

#endif // __AK_RENDERER_COMPONENT__
