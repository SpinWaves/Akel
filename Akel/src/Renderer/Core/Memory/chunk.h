// This file is a part of Akel
// Authors : @kbz_8
// Created : 24/09/2021
// Updated : 08/05/2022

#ifndef __AK_VK_GPU_MEMORY_CHUNK__
#define __AK_VK_GPU_MEMORY_CHUNK__

#include <Akpch.h>

namespace Ak
{
    struct GPU_Mem_Chunk
    {
        VkDeviceMemory memory = VK_NULL_HANDLE;
        unsigned int offset = 0;
        unsigned int size = 0;
    };
}

#endif // __AK_VK_GPU_MEMORY_CHUNK__
