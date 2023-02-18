// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 18/02/2023

#ifndef __AK_BUILTIN_SHADERS__
#define __AK_BUILTIN_SHADERS__

#include <Akpch.h>

namespace Ak
{
	const std::string default_vertex_shader = R"nzsl(
		[nzsl_version("1.0")]
		module;

		import * from Akel.VertexInput;
		import * from Akel.VertexOutput;
		import * from Akel.Matrices;

		external
		{
			[set(0), binding(0)] matrices: uniform[Matrices],
		}

		[entry(vert)]
		fn main(input: VertIn) -> VertOut
		{
			let output: VertOut;
			output.pos = matrices.projection * matrices.view * matrices.model * vec4[f32](input.pos, 1.0);
			output.color = input.color;
			output.uv = input.uv;
			return output;
		}
	)nzsl";

	const std::string default_fragment_shader = R"nzsl(
		[nzsl_version("1.0")]
		module;

		import * from Akel.VertexOutput;
		import * from Akel.FragmentOutput;

		external
		{
			[set(1), binding(0)] texSampler: sampler2D[f32]
		}

		[entry(frag)]
		fn main(input: VertOut) -> FragOut
		{
			let output: FragOut;
			output.color = input.color * texSampler.Sample(input.uv);
			return output;
		}
	)nzsl";

	const std::string skybox_vertex_shader = R"nzsl(
		[nzsl_version("1.0")]
		module SkyboxVertexShader;

		import * from Akel.Matrices;

		external
		{
			[set(0), binding(0)] matrices: uniform[Matrices],
		}

		struct VertIn
		{
			[location(0)] position: vec3[f32]
		}

		[export]
		struct VertOut
		{
			[location(0)] uvw: vec3[f32],
			[builtin(position)] position: vec4[f32]
		}

		[entry(vert)]
		fn main(input: VertIn) -> VertOut
		{
			let rotationMat = matrices.view;
			rotationMat[3].xyz = vec3[f32](0.0, 0.0, 0.0);

			let output: VertOut;
			output.position = matrices.projection * rotationMat * vec4[f32](input.position, 1.0);
			output.uvw = input.position.xyz;

			return output;
		}
	)nzsl";

	const std::string skybox_fragment_shader = R"nzsl(
		[nzsl_version("1.0")]
		module;

		import VertOut from SkyboxVertexShader;

		external
		{
			[set(1), binding(0)] skybox: sampler_cube[f32]
		}

		struct FragOut
		{
			[location(0)] color: vec4[f32],
			[builtin(frag_depth)] depth: f32
		}

		[entry(frag)]
		[depth_write(greater)]
		fn main(input: VertOut) -> FragOut
		{
			let output: FragOut;
			output.color = skybox.Sample(input.uvw);
			output.depth = 1.0;

			return output;
		}
	)nzsl";
}

#endif
