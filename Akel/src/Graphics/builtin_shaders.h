// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 21/02/2023

#ifndef __AK_BUILTIN_SHADERS__
#define __AK_BUILTIN_SHADERS__

#include <Akpch.h>

namespace Ak
{
	const std::string forward_vertex_shader =
		#include <Graphics/Resources/Shaders/forward.vert.nzsl>
	;
	const std::string forward_fragment_shader =
		#include <Graphics/Resources/Shaders/forward.frag.nzsl>
	;
	const std::string skybox_vertex_shader =
		#include <Graphics/Resources/Shaders/skybox.vert.nzsl>
	;
	const std::string skybox_fragment_shader =
		#include <Graphics/Resources/Shaders/skybox.frag.nzsl>
	;
}

#endif
