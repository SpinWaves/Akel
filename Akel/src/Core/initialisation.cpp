// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/10/2021
// Updated : 15/10/2023

#include <Core/profile.h>

#define VOLK_IMPLEMENTATION

#ifdef AK_PLATFORM_WINDOWS
	#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(AK_PLATFORM_OSX)
	#define VK_USE_PLATFORM_MACOS_MVK
#elif defined(AK_PLATFORM_LINUX)
	#define VK_USE_PLATFORM_XLIB_KHR
#else
	#error "Akel's renderer doesn't know how to run on this system"
#endif

#include <volk.h>

#include <Renderer/Core/render_core.h>
#include <Core/softwareInfo.h>
#include <Core/application.h>
#include <Core/vfs.h>

namespace Ak
{
	namespace Core
	{
		void initCpuInfo();
		namespace memory::internal
		{
			void init();
		}
	}
	
	extern Core::ProjectFile* __main_app_project_file;

    bool initAkel(AkelInstance* project)
    {
		/*
		#if defined(AK_64BITS)
			if(sizeof(void*) != 8)
			{
				Core::log::report(ERROR, "Conflict of system architecture detection");
			    return false;
			}
			Core::log::report("architecture: 64bits");
		#elif defined(AK_32BITS)
			if(sizeof(void*) != 4)
			{
				Core::log::report(ERROR, "Conflict of system architecture detection");
			    return false;
			}
			Core::log::report("architecture: 32bits");
		#endif
		if(std::strcmp(AK_arch, "x86") != 0)
		{
			Core::log::report(ERROR, "Akel can only run on x86 architecture, you are trying to run it on a " AK_arch " architecture");
			return false;
		}
		Core::log::report("arch: " AK_arch);

*/
		if(volkInitialize() != VK_SUCCESS)
		{
			Core::log::report(ERROR, "Vulkan is not supported");
			return false;
		}
		if(!Core::isVulkanSupported())
		{
			Core::log::report(ERROR, "Vulkan is not supported");
			return false;
		}

		__main_app_project_file = &project->_project_file;

		if(project->project_file_name != "")
			project->_project_file.setName(project->project_file_name);
		project->_project_file.setDir(VFS::resolve(project->project_file_path.string()));
		
		project->_project_file.initProjFile(project->project_file_force_raw_json);

		project->_project_file.archive()["enable_warning_console_message"] = project->enable_warning_console_message;
		project->_project_file.archive()["vk_enable_message_validation_layer"] = project->vk_enable_message_validation_layer;
		project->_project_file.archive()["vk_force_disable_validation_layers"] = project->vk_force_disable_validation_layers;
		project->_project_file.archive()["memory_manager_enable_fixed_allocator"] = project->memory_manager_enable_fixed_allocator;
		project->_project_file.archive()["use_default_resource_system"] = project->use_default_resource_system;

		Core::memory::internal::init();

		if(project->use_default_resource_system)
			VFS::initResSystem();

		return true;
    }
}
