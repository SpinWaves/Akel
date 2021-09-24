// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 24/09/2021

#ifndef __AK_VULKAN_GLOBAL_BUFFER__
#define __AK_VULKAN_GLOBAL_BUFFER__

namespace Ak
{
    class GlobalBuffer
    {
        public:
            explicit GlobalBuffer();

            ~GlobalBuffer();

        private:
            std::vector<std::pair<unsigned int, size_t>> _vertexBuff;
            std::vector<std::pair<unsigned int, size_t>> _indexBuff;
            std::vector<std::pair<unsigned int, size_t>> _uniformBuff;
    };
}

#endif // __AK_VULKAN_GLOBAL_BUFFER__
