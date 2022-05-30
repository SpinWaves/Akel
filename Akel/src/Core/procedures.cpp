// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/10/2021
// Updated : 30/05/2022

#include <Audio/audio.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
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

		if(project->project_file_name != "")
			Core::ProjectFile::setName(project->project_file_name);
		if(project->project_file_path != "")
			Core::ProjectFile::setDir(project->project_file_path);
		Core::ProjectFile::initProjFile();

		Core::ProjectFile::setBoolValue("enable_warning_console_message", project->enable_warning_console_message);
		Core::ProjectFile::setBoolValue("vk_enable_message_validation_layer", project->vk_enable_message_validation_layer);
		Core::ProjectFile::setBoolValue("memory_manager_enable_fixed_allocator", project->memory_manager_enable_fixed_allocator);
		Core::ProjectFile::setBoolValue("imgui_vk_debug_report", project->imgui_vk_debug_report);
		Core::ProjectFile::setBoolValue("imgui_vk_unlimited_framerate", project->imgui_vk_unlimited_framerate);

		MemoryManager::useMemoryManager(project->use_memory_manager);
		MemoryManager::init();

		return true;
    }
}
