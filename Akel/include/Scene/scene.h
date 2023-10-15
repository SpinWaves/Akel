// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 14/10/2023

#ifndef __AK_SCENE__
#define __AK_SCENE__

#include <Akpch.h>
#include <Utils/fStrings.h>
#include <Core/Memory/akel_unique_ptr.h>
#include <Core/Memory/akel_shared_ptr.h>
#include <Renderer/Pipeline/shaders_library.h>
#include <Platform/input.h>

namespace Ak
{
	enum class shaderlang : uint8_t
	{
		spirv = 0,
		nzsl = 1,
	};

	enum class shaderType : uint8_t
	{
		vertex = 0,
		fragment = 1,
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

			template <shaderlang lang, shaderType type>
			void loadCustomShader(std::filesystem::path path);
			inline void loadCustomShader(shaderType type, std::vector<uint32_t> byte_code)
			{
				std::shared_ptr<Shader> shader = create_shared_ptr_w<Shader>(std::move(byte_code), _renderer);
				_forward_shaders[static_cast<uint8_t>(type)] = ShadersLibrary::get().addShaderToLibrary(std::move(shader));
			}

			Entity createEntity();
			Entity createEntity(const std::string& name);

			entt::registry& getRegistry() noexcept;

			template <typename T, typename ... Args>
			void addCamera(Args&& ... args);

			inline const fString& getName() const noexcept { return _name; }
			inline const std::filesystem::path& getFilePath() const { return _filepath; }
			inline uint32_t getID() const noexcept { return _id; }

			~Scene();

		private:
			void _loadCustomShader(shaderType type, shaderlang lang, std::filesystem::path path);

		private:
			std::array<ShaderID, 2> _forward_shaders;
			std::filesystem::path _filepath;
			class RendererComponent* _renderer = nullptr;
			UniquePtr<Cam::BaseCamera> _camera;
			UniquePtr<class ShaderLoader> _loader;
			UniquePtr<class EntityManager> _entity_manager;
			fString _name;
			uint32_t _id = -1;
			uint32_t _entity_count = 0;
			bool _first_update = true;
	};
}

#include <Scene/scene.inl>

#endif
