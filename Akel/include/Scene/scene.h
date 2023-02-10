// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 08/02/2023

#ifndef __AK_SCENE__
#define __AK_SCENE__

#include <Akpch.h>
#include <Platform/input.h>
#include <Utils/fStrings.h>
#include <Graphics/entity.h>
#include <Core/profile.h>
#include <Core/Memory/uniquePtrWrapper.h>

namespace Ak
{
	enum class shaderlang
	{
		spirv,
		nzsl
	};

	class AK_API Scene
	{
		friend class Skybox;

		public:
			Scene(fString name = "Empty scene");

			void onAttach(class RendererComponent* renderer, uint32_t id) noexcept;
			void onPreRender();
			void onRender3D();
			void onRender2D();
			void onQuit();

			inline void loadCustomShader(std::vector<uint32_t> byte_code) { _shaders.push_back(std::move(byte_code)); }

			template <shaderlang lang>
			inline void loadCustomShader(std::filesystem::path path)
			{
				if(lang == shaderlang::spirv)
					_shaders.push_back(load_spirv_from_file(path.c_str()));
				else
					_loadCustomShader(lang, std::move(path));
			}

			inline void setCullMode(VkCullModeFlags culling) noexcept { _cull_mode = culling; }

			void add_2D_entity(Entity2D entity);
			void add_3D_entity(Entity3D entity);

			~Scene();

		private:
			void _loadCustomShader(shaderlang lang, std::filesystem::path path);

			std::vector<class Entity3D> _3D_entities;
			std::vector<class Entity2D> _2D_entities;

			GraphicPipeline _pipeline;
			std::vector<std::vector<uint32_t>> _shaders;
			VkCullModeFlags _cull_mode;
			
			Unique_ptr<class ShaderLoader> _loader;
			fString _name;
			class RendererComponent* _renderer = nullptr;
			uint32_t _id = -1;
	};
}

#endif
