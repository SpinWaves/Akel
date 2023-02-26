// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/02/2023
// Updated : 24/02/2023

#ifndef __AK_SHADERS_LIBRARY__
#define __AK_SHADERS_LIBRARY__

#include <Akpch.h>
#include <Renderer/Pipeline/vk_shader.h>
#include <Utils/selfInstance.h>

namespace Ak
{
	using ShaderID = uint32_t;
	constexpr ShaderID nullshader = 0;

	class ShadersLibrary : public SelfInstance<ShadersLibrary>
	{
		public:
			ShadersLibrary() = default;

			std::shared_ptr<Shader> getShader(ShaderID id);
			ShaderID addShaderToLibrary(std::shared_ptr<Shader> shader);
			void removeShaderFromLibrary(ShaderID id);

			void clearLibrary();

			~ShadersLibrary() = default;

		private:
			std::unordered_map<ShaderID, std::shared_ptr<Shader>> _cache;
			ShaderID _current_id = 1;
	};
}

#endif
