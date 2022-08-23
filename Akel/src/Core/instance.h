// This file is a part of the Akel
// Authors : @kbz_8
// Created : 16/10/2021
// Updated : 21/08/2022

#ifndef __AK_INSTANCE__
#define __AK_INSTANCE__

#include <Akpch.h>

namespace Ak
{
    struct AkelInstance
    {
        std::string project_file_path = "";
        std::string project_file_name = "";
        bool use_memory_manager = true;
        bool memory_manager_enable_fixed_allocator = true;
        bool vk_enable_message_validation_layer = false;
        bool use_system_dialog_boxes = false;
        bool enable_warning_console_message = true;
        bool vk_force_disable_validation_layers = false;
    };
}

#endif // __AK_INSTANCE__
