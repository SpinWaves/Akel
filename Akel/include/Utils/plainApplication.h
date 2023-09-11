// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/03/2022
// Updated : 11/09/2023

#ifndef __AK_PLAIN_APPLICATION__
#define __AK_PLAIN_APPLICATION__

#include <Core/profile.h>
#include <Core/application.h>

namespace Ak
{
	class AK_API PlainApplication
	{
		public:
			PlainApplication(Application& app, const char* name = "Akel Window");

			void add_scene(class Scene* scene) noexcept;
			void remove_scene(class Scene* scene) noexcept;
			void remove_scene(uint32_t id) noexcept;
			void switch_to_scene(uint32_t id) noexcept;

			template <typename T, typename ... Args>
			inline T* add_component(Args&& ... args) { return _app.add_component<T>(std::forward<Args>(args)...); }
			inline Component* add_component(Component* component) { return _app.add_component(component); }
			inline void remove_component(Component* component) { _app.remove_component(component); }
			inline void remove_component(const char* name) { _app.remove_component(name); }
			inline Component* get_component(const char* name) { return _app.get_component(name); }
			inline Component* get_component(size_t index) { return _app.get_component(index); }

			template <typename T>
			inline T get_component_as(const char* name) { return static_cast<T>(get_component(name)); }
			template <typename T>
			inline T get_component_as(size_t index) { return static_cast<T>(get_component(index)); }

			inline class WindowComponent* getWindow() noexcept { return _window; }
			inline class RendererComponent* getRenderer() noexcept { return _renderer; }
			inline class SceneManager* getSceneManager() noexcept { return _scene_manager; }

			~PlainApplication() = default;

		private:
			Application& _app;
			class WindowComponent* _window = nullptr;
			class RendererComponent* _renderer = nullptr;
			class SceneManager* _scene_manager = nullptr;
	};
}

#endif // __AK_PLAIN_APPLICATION__
