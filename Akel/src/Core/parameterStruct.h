// This file is a part of the Akel
// CREATED : 16/10/2021
// UPDATED : 12/11/2021

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
        bool memory_manager_enable_jam_allocator = true;
        bool vk_enable_message_validation_layer = false;
        bool unique_ptr_wrapper_enable_debug_message = false;
        bool use_system_dialog_boxes = false;
    };
}

#endif // __AK_PARAMETER_STRUCT__
