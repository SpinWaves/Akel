// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 07/02/2023

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
			[set(1), binding(1)] texSampler: sampler2D[f32]
		}

		[entry(frag)]
		fn main(input: VertOut) -> FragOut
		{
			let output: FragOut;
			output.color = input.color * texSampler.Sample(input.uv);
			return output;
		}
	)nzsl";
}

#endif
