// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/10/2021
// Updated : 22/07/2022

#include <Audio/audio.h>
#include <Renderer/Core/render_core.h>
#include "softwareInfo.h"

namespace Ak
{
	namespace Core
	{
		std::string getMainDirPath();
	}
	
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

		if(!Core::isVulkanSupported())
			Core::log::report(FATAL_ERROR, "Vulkan is not supported");

		if(project->project_file_name != "")
			Core::ProjectFile::setName(project->project_file_name);
		if(project->project_file_path != "")
			Core::ProjectFile::setDir(project->project_file_path);
		else
			Core::ProjectFile::setDir(Core::getMainDirPath());
		
		Core::ProjectFile::initProjFile();

		Core::ProjectFile::setBoolValue("enable_warning_console_message", project->enable_warning_console_message);
		Core::ProjectFile::setBoolValue("vk_enable_message_validation_layer", project->vk_enable_message_validation_layer);
		Core::ProjectFile::setBoolValue("vk_force_disable_validation_layers", project->vk_force_disable_validation_layers);
		Core::ProjectFile::setBoolValue("memory_manager_enable_fixed_allocator", project->memory_manager_enable_fixed_allocator);

		MemoryManager::useMemoryManager(project->use_memory_manager);
		MemoryManager::init();

		return true;
    }
}
