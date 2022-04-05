// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/04/2022
// Updated : 05/04/2022

#ifndef __AK_SHADER_MANAGER__
#define __AK_SHADER_MANAGER__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
	class Shader;

	class ShaderManager : public SelfInstance<ShaderManager>
	{
		public:

		private:
			std::vector<Shader> _shaders;
	};
}

#endif // __AK_SHADER_MANAGER__
