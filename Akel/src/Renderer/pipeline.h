// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 06/06/2021

#ifndef __AK_VK_PIPELINE__
#define __AK_VK_PIPELINE__

#include <Akpch.h>

#include <Renderer/device.h>

namespace Ak
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

#endif // __AK_VK_PIPELINE__
