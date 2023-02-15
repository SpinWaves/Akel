// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 15/02/2023

#ifndef __AK_FORWARD_DATA__
#define __AK_FORWARD_DATA__

#include <Akpch.h>
#include <Renderer/render_command.h>
#include <Renderer/images/texture.h>

namespace Ak
{
	struct ForwardData
	{
		Texture* texture = nullptr;
		CommandDataQueue command_queue;
	};
}

#endif
