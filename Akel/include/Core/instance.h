// This file is a part of the Akel
// Authors : @kbz_8
// Created : 16/10/2021
// Updated : 27/01/2023

#ifndef __AK_INSTANCE__
#define __AK_INSTANCE__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
    class AK_API AkelInstance
    {
		public:
			AkelInstance() = default;

			std::string project_file_path = "";
			std::string project_file_name = "";
			bool memory_manager_enable_fixed_allocator = true;
			bool vk_enable_message_validation_layer = false;
			bool use_system_dialog_boxes = false;
			bool enable_warning_console_message = true;
			bool vk_force_disable_validation_layers = false;
			bool use_default_resource_system = true;

			~AkelInstance() = default;

		private:
			friend bool initAkel(AkelInstance* project);
			Core::ProjectFile _project_file;
    };
}

#endif // __AK_INSTANCE__