// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 19/12/2022

#ifndef __AK_SCENE__
#define __AK_SCENE__

#include <Akpch.h>
#include <Platform/input.h>
#include <Utils/fStrings.h>
#include <Graphics/entity.h>

namespace Ak
{
	class Scene
	{
		public:
			Scene(fString name = "Empty scene", class WindowComponent* window = nullptr);

			void onAttach(uint32_t id) noexcept;
			void onPreRender();
			void onRender3D();
			void onRender2D();
			void onQuit();

			inline void loadCustomShader(std::vector<uint32_t> byte_code) { _shaders.push_back(std::move(byte_code)); }
			inline void loadCustomShader(fString path) { _shaders.push_back(load_spirv_from_file(std::move(path))); }

			inline void setCullMode(VkCullModeFlags culling) noexcept { _cull_mode = culling; }

			void add_2D_entity(Entity2D entity);
			void add_3D_entity(Entity3D entity);

			~Scene() = default;

		private:
			std::vector<class Entity3D> _3D_entities;
			std::vector<class Entity2D> _2D_entities;

			GraphicPipeline _3D_pipeline;
			GraphicPipeline _2D_pipeline;
			std::vector<std::vector<uint32_t>> _shaders;
			VkCullModeFlags _cull_mode;
			
			fString _name;
			class WindowComponent* _window = nullptr;
			uint32_t _id = -1;
	};
}

#endif
