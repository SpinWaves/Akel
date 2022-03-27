// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#ifndef __AK_VK_SHADERS__
#define __AK_VK_SHADERS__

#include <Akpch.h>

namespace Ak
{
	class Shader
	{
		public:
			class VertexInput
			{
				public:
					VertexInput();
			};

			class UniformInput
			{
				public:
					UniformInput();
			};

			class UniformBlock
			{
				public:
					UniformBlock();

					~UniformBlock() = default;

				private:
					std::vector<UniformInput> _block;
			};

			Shader();

			~Shader();
	};
}

#endif // __AK_VK_SHADERS__
