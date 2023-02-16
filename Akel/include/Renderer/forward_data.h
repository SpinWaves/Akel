// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 16/02/2023

#ifndef __AK_FORWARD_DATA__
#define __AK_FORWARD_DATA__

#include <Akpch.h>
#include <Renderer/render_command.h>
#include <Renderer/Images/texture.h>

namespace Ak
{
	struct ForwardData
	{
		std::vector<std::reference_wrapper<Shader>> shaders;
		CommandDataQueue command_queue;
		Texture* texture = nullptr;
	};
}

#endif
