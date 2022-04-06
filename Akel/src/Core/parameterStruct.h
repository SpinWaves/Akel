// This file is a part of the Akel
// Authors : @kbz_8
// Created : 16/10/2021
// Updated : 06/04/2022

#ifndef __AK_PARAMETER_STRUCT__
#define __AK_PARAMETER_STRUCT__

#include <Core/core.h>

namespace Ak
{
    struct AkelInstance
    {
        std::string project_file_path = "";
        std::string project_file_name = "";
        bool use_memory_manager = true;
        bool memory_manager_enable_fixed_allocator = true;
        bool vk_enable_message_validation_layer = false;
        bool unique_ptr_wrapper_enable_debug_message = false;
        bool use_system_dialog_boxes = false;
        bool enable_warning_console_message = true;
        bool imgui_vk_debug_report = true;
        bool imgui_vk_unlimited_framerate = false;
    };
}

#endif // __AK_PARAMETER_STRUCT__
