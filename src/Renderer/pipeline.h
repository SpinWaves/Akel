// This file is a part of AtlasEngine
// CREATED : 05/06/2021
// UPDATED : 06/06/2021

#ifndef __AE_VK_PIPELINE__
#define __AE_VK_PIPELINE__

#include <AEpch.h>

#include <Renderer/device.h>

namespace AE
{
    class Pipeline : public Device
    {
        public:
			Pipeline();
            void createGraphicsPipeline(const char* vert, const char* frag);
            static std::vector<char> readFile(const std::string& filename);
            VkShaderModule createShaderModule(const std::vector<char>& code);

            VkPipelineLayout pipelineLayout;
            VkPipeline graphicsPipeline;
    };
}

#endif // __AE_VK_PIPELINE__
