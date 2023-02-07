// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 07/02/2023

#ifndef __AK_NZSL_BUILTIN_MODULES__
#define __AK_NZSL_BUILTIN_MODULES__

#include <Akpch.h>

namespace Ak_nzsl
{
	const std::string vertex_input = R"nzsl(
		[nzsl_version("1.0")]
		module Akel.VertexInput;

		[export]
		struct VertIn
		{
			[location(0)] pos: vec3[f32],
			[location(1)] color: vec4[f32],
			[location(2)] uv: vec2[f32]
		}
	)nzsl";

	const std::string vertex_output = R"nzsl(
		[nzsl_version("1.0")]
		module Akel.VertexOutput;

		[export]
		struct VertOut
		{
			[location(0)] color: vec4[f32],
			[location(1)] uv: vec2[f32],
			[builtin(position)] pos: vec4[f32]
		}
	)nzsl";

	const std::string matrices = R"nzsl(
		[nzsl_version("1.0")]
		module Akel.Matrices;

		[export, layout(std140)]
		struct Matrices
		{
			model: mat4[f32],
			view: mat4[f32],
			projection: mat4[f32]
		}
	)nzsl";

	const std::string fragment_output = R"nzsl(
		[nzsl_version("1.0")]
		module Akel.FragmentOutput;

		[export]
		struct FragOut
		{
			[location(0)] color: vec4[f32]
		}
	)nzsl";
}

#endif
