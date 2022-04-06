// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/04/2022
// Updated : 06/04/2022

#ifndef __AK_SHADER_MANAGER__
#define __AK_SHADER_MANAGER__

#include <Akpch.h>
#include "vk_shader.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
	class ShaderManager : public SelfInstance<ShaderManager>
	{
		public:
			inline void add_shader(Shader shader) { _shaders.push_back(shader); }
			inline void remove_shader(Shader& shader)
			{
				auto it = std::find_if(_shader.begin(), _shader.end(), [&](Shader& ref){ return ref == shader; });
				if(it != _shader.end())
					_shader.erase(it);
			}
			inline void remove_shader(const fString name)
			{
				auto it = std::find_if(_shader.begin(), _shader.end(), [&](Shader& ref){ return ref.getName() == shader.getName()); });
				if(it != _shader.end())
					_shader.erase(it);
			}
			inline Shader& find(const fString& name)
			{
				auto it = std::find_if(_shader.begin(), _shader.end(), [&](Shader& ref){ return ref.getName() == shader.getName()) });
				if(it != _shader.end())
					return *it;
			}

		private:
			std::vector<Shader> _shaders;
	};
}

#endif // __AK_SHADER_MANAGER__
