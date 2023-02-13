// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 13/02/2023

#ifndef __AK_SCENE__
#define __AK_SCENE__

#include <Akpch.h>
#include <Utils/fStrings.h>
#include <Core/Memory/uniquePtrWrapper.h>

namespace Ak
{
	enum class shaderlang
	{
		spirv,
		nzsl
	};

	class Enity;

	class AK_API Scene
	{
		public:
			Scene(fString name = "Empty scene");

			void onAttach(class RendererComponent* renderer, uint32_t id) noexcept;
			void onRender();
			void onUpdate(float timestep)
			void onQuit();

			template <shaderlang lang>
			void loadCustomShader(std::filesystem::path path);
			inline void loadCustomShader(std::vector<uint32_t> byte_code) { _shaders.push_back(std::move(byte_code)); }

			Entity createEntity();
			Entity createEntity(const std::string& name);

			inline entt::registry& getRegistry() noexcept { return _entity_manager.getRegistry(); }

			inline void setCullMode(VkCullModeFlags culling) noexcept { _cull_mode = culling; }

			~Scene();

		private:
			void _loadCustomShader(shaderlang lang, std::filesystem::path path);

			GraphicPipeline _pipeline;
			std::vector<std::vector<uint32_t>> _shaders;
			class RendererComponent* _renderer = nullptr;
			VkCullModeFlags _cull_mode;
			
			Unique_ptr<class ShaderLoader> _loader;
			Unique_ptr<class EntityManager> _entity_manager;
			fString _name;
			uint32_t _id = -1;
	};
}

#include <Scene/scene.inl>

#endif
