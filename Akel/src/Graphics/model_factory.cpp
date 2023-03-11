// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/03/2023
// Updated : 11/03/2023

#include <Graphics/model_factory.h>
#include <Maths/vec3.h>
#include <Maths/vec4.h>

namespace Ak
{
	Model createCube()
	{
		const Maths::Vec3f position(0.0f, 0.0f, 0.0f);
		const Maths::Vec3f scale(1.0f, 1.0f, 1.0f);
		const Maths::Vec4f color(1.0f, 1.0f, 1.0f, 1.0f);

		const std::vector<Vertex> vertexData = {
			{{position.X, position.Y + scale.Y, position.Z + scale.Z}, 			color, {0.0f, 0.0f}},
			{{position.X + scale.X, position.Y + scale.Y, position.Z + scale.Z},color, {1.0f, 0.0f}},
			{{position.X + scale.X, position.Y, position.Z + scale.Z}, 			color, {1.0f, 1.0f}},
			{{position.X, position.Y, position.Z + scale.Z}, 					color, {0.0f, 1.0f}},
			{{position.X, position.Y + scale.Y, position.Z}, 					color, {1.0f, 0.0f}},
			{{position.X + scale.X, position.Y + scale.Y, position.Z}, 			color, {1.0f, 1.0f}},
			{{position.X + scale.X, position.Y, position.Z}, 					color, {0.0f, 1.0f}},
			{{position.X, position.Y, position.Z,}, 							color, {0.0f, 0.0f}},
			{{position.X, position.Y + scale.Y, position.Z}, 					color, {1.0f, 0.0f}},
			{{position.X, position.Y + scale.Y, position.Z + scale.Z}, 			color, {1.0f, 1.0f}},
			{{position.X, position.Y, position.Z + scale.Z}, 					color, {0.0f, 1.0f}},
			{{position.X, position.Y, position.Z}, 								color, {0.0f, 0.0f}},
			{{position.X + scale.X, position.Y + scale.Y, position.Z + scale.Z},color, {1.0f, 0.0f}},
			{{position.X + scale.X, position.Y + scale.Y, position.Z}, 			color, {1.0f, 1.0f}},
			{{position.X + scale.X, position.Y, position.Z}, 					color, {0.0f, 1.0f}},
			{{position.X + scale.X, position.Y, position.Z + scale.Z}, 			color, {0.0f, 0.0f}},
			{{position.X, position.Y + scale.Y, position.Z}, 					color, {0.0f, 0.0f}},
			{{position.X + scale.X, position.Y + scale.Y, position.Z}, 			color, {1.0f, 0.0f}},
			{{position.X + scale.X, position.Y + scale.Y, position.Z + scale.Z},color, {1.0f, 1.0f}},
			{{position.X, position.Y + scale.Y, position.Z + scale.Z}, 			color, {0.0f, 1.0f}},
			{{position.X, position.Y, position.Y + scale.Z}, 					color, {1.0f, 0.0f}},
			{{position.X + scale.X, position.Y, position.Z + scale.Z}, 			color, {1.0f, 1.0f}},
			{{position.X + scale.X, position.Y, position.Z}, 					color, {0.0f, 1.0f}},
			{{position.X, position.Y, position.Z}, 								color, {0.0f, 0.0f}}
		};

		const std::vector<uint32_t> indexData = {
			0,  1,  2,   2,  3,  0,  // top
			4,  5,  6,   6,  7,  4,  // back
			8,  9, 10,  10, 11,  8,  // left
			12, 13, 14,  14, 15, 12, // front
			16, 17, 18,  18, 19, 16, // right
			20, 21, 22,  22, 23, 20  // bottom
		};
		Mesh mesh(std::move(vertexData), std::move(indexData));
		return {std::move(mesh)};
	}

	Model createQuad()
	{

	}
}
