// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/10/2021
// Updated : 22/12/2022

#include <Core/profile.h>

#define VOLK_IMPLEMENTATION

#ifdef AK_PLATFORM_WINDOWS
	#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(AK_PLATFORM_OSX)
	#define VK_USE_PLATFORM_MACOS_MVK
#elif defined(AK_PLATFORM_LINUX)
	#define VK_USE_PLATFORM_XLIB_KHR
#else
	#error "Akel's renderer don't know how to run on this system"
#endif

#include <volk.h>

#include <Renderer/Core/render_core.h>
#include "softwareInfo.h"
#include "application.h"

namespace Ak
{
	namespace Core
	{
		std::string getMainDirPath();
		void initCpuInfo();
	}
	
	extern Core::ProjectFile* __main_app_project_file;

    bool initAkel(AkelInstance* project)
    {
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
		if(project->project_file_path != "")
			project->_project_file.setDir(project->project_file_path);
		else
			project->_project_file.setDir(Core::getMainDirPath());
		
		project->_project_file.initProjFile();

		project->_project_file.setBoolValue("enable_warning_console_message", project->enable_warning_console_message);
		project->_project_file.setBoolValue("vk_enable_message_validation_layer", project->vk_enable_message_validation_layer);
		project->_project_file.setBoolValue("vk_force_disable_validation_layers", project->vk_force_disable_validation_layers);
		project->_project_file.setBoolValue("memory_manager_enable_fixed_allocator", project->memory_manager_enable_fixed_allocator);

		Core::initCpuInfo();
		MemoryManager::init();

		return true;
    }
}
