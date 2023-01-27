// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/03/2022
// Updated : 12/12/2022

#ifndef __AK_PLAIN_APPLICATION__
#define __AK_PLAIN_APPLICATION__

#include <Core/application.h>

namespace Ak
{
	class PlainApplication : public Application
	{
		public:
			PlainApplication(const char* name = "Akel Window");

			void add_scene(class Scene* scene) noexcept;
			void remove_scene(class Scene* scene) noexcept;
			void remove_scene(uint32_t id) noexcept;
			void switch_to_scene(uint32_t id) noexcept;

			inline class WindowComponent* getWindow() noexcept { return _window; }

			~PlainApplication() = default;

		private:
			class WindowComponent* _window = nullptr;
			class RendererComponent* _renderer = nullptr;
			class SceneManager* _scene_manager = nullptr;
	};
}

#endif // __AK_PLAIN_APPLICATION__
