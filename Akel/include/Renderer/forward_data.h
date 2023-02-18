// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 18/02/2023

#ifndef __AK_FORWARD_DATA__
#define __AK_FORWARD_DATA__

#include <Akpch.h>
#include <Renderer/render_command.h>
#include <Renderer/Images/texture.h>
#include <Renderer/Pipeline/shaders_library.h>

namespace Ak
{
	struct ForwardData
	{
		CommandDataQueue command_queue;
		std::vector<ShaderID> shaders;
		std::shared_ptr<Texture> texture = nullptr;
	};
}

#endif
