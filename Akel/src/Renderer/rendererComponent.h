// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 06/03/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Graphics/entity.h>
#include <Platform/window.h>

namespace Ak
{
    constexpr const int MAX_FRAMES_IN_FLIGHT = 2;

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        inline bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
    };

	struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct UniformBufferObject
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

    #ifdef AK_DEBUG
        constexpr const bool enableValidationLayers = true;
    #else
        constexpr const bool enableValidationLayers = false;
    #endif

    enum class shader
    {
        basic_2D,
        basic_3D
        // More default shaders will come in the future
    };

    class RendererComponent : public Component
    {
        public:
            RendererComponent(WindowComponent* win, shader internal); 
            RendererComponent(WindowComponent* win);
            RendererComponent(shader internal); 
            RendererComponent();

            void onAttach() override;
            void onRender() override;
            void onQuit() override;

            inline void setShader(std::string vertexShader, std::string fragmentShader) { _vertexShader = std::move(vertexShader); _fragmentShader = std::move(fragmentShader); }
            void useShader(shader internal);
            inline void render_to_window(WindowComponent* win) noexcept { window = win; }
            
            inline void add_entity(Entity2D& entity) { entities2D.push_back(entity); }
            inline void add_entity(Entity3D& entity) { entities3D.push_back(entity); }

            inline void setClearColor(float r, float g, float b, float a) noexcept { clearColor.color.float32[0] = r; clearColor.color.float32[1] = g; clearColor.color.float32[2] = b; clearColor.color.float32[3] = a; }
            inline static void requireFrameBufferResize() noexcept { framebufferResized = true; }

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
            void recreateSwapChain();

            // Image views
            void createImageViews();

            // Pipeline graphique
            void createGraphicsPipeline();
            VkShaderModule createShaderModule(const std::vector<uint32_t>& code);

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
            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
            void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
            void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
            void createVertexBuffer();
            void createIndexBuffer();

            // UniformBuffer
            void createDescriptorSetLayout();
            void createUniformBuffers();
            void updateUniformBuffer(uint32_t currentImage);
            void createDescriptorPool();
            void createDescriptorSets();

            std::vector<Entity2D> entities2D;
            std::vector<Entity3D> entities3D;

            std::string _vertexShader;
            std::string _fragmentShader;

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
            inline static bool framebufferResized = false;

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

            // UniformBuffer
            VkDescriptorSetLayout descriptorSetLayout;
            std::vector<VkBuffer> uniformBuffers;
            std::vector<VkDeviceMemory> uniformBuffersMemory;
            VkDescriptorPool descriptorPool;
            std::vector<VkDescriptorSet> descriptorSets;

            WindowComponent* window = nullptr;

            bool _instanceInitialized = false;

            VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    };
}

#endif // __AK_RENDERER_COMPONENT__
