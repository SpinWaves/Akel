// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 30/05/2023

#ifndef __AK_SCENE__
#define __AK_SCENE__

#include <Akpch.h>
#include <Utils/fStrings.h>
#include <Core/Memory/uniquePtrWrapper.h>
#include <Core/Memory/sharedPtrWrapper.h>
#include <Renderer/Pipeline/shaders_library.h>
#include <Platform/input.h>

namespace Ak
{
	enum class shaderlang
	{
		spirv,
		nzsl
	};

	namespace Cam
	{
		class BaseCamera;
	}

	class Entity;

	class AK_API Scene
	{
		friend class SceneRenderer;
		friend class SceneSerializer;

		public:
			Scene(fString name = "Empty scene");

			void onAttach(class RendererComponent* renderer, uint32_t id) noexcept;
			void onUpdate(float timestep);
			void onEvent(Input& input);
			void onQuit();

			template <shaderlang lang>
			void loadCustomShader(std::filesystem::path path);
			inline void loadCustomShader(std::vector<uint32_t> byte_code)
			{
				std::shared_ptr<Shader> shader = create_shared_ptr_w<Shader>(std::move(byte_code), _renderer);
				_forward_shaders.push_back(ShadersLibrary::get().addShaderToLibrary(std::move(shader)));
			}

			Entity createEntity();
			Entity createEntity(const std::string& name);

			entt::registry& getRegistry() noexcept;

			template <typename T, typename ... Args>
			void addCamera(Args&& ... args);

			inline const fString& getName() const noexcept { return _name; }
			inline uint32_t getID() const noexcept { return _id; }

			~Scene();

		private:
			void _loadCustomShader(shaderlang lang, std::filesystem::path path);

		private:
			std::vector<ShaderID> _forward_shaders;
			class RendererComponent* _renderer = nullptr;
			Unique_ptr<Cam::BaseCamera> _camera;
			Unique_ptr<class ShaderLoader> _loader;
			Unique_ptr<class EntityManager> _entity_manager;
			fString _name;
			uint32_t _id = -1;
			uint32_t _entity_count = 0;
			bool _first_update = true;
	};
}

#include <Scene/scene.inl>

#endif
