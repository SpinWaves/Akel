// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/11/2022
// Updated : 23/11/2022

#ifndef __AK_SCENE_MANAGER__
#define __AK_SCENE_MANAGER__

#include <Akpch.h>
#include <Core/Components/baseComponent.h>

namespace Ak
{
	class SceneManager : public Component
	{
		public:
			SceneManager() = default;

			void onAttach() override;
			void update() override;
			void onEvent(Input& in) override;
			void onRender() override;
			void onQuit() override;

			inline void add_scene(class Scene* scene)
			{
				if(scene != nullptr)
					_scenes.push_back(scene);
				if(_current_scene_id == -1)
					_current_scene_id = 0;
				scene->onAttach(_scenes.size() - 1);
			}
			void remove_scene(class Scene* scene);
			void remove_scene(uint32_t id);

			inline void switch_to_scene(uint32_t id) noexcept
			{
				if(id > _scenes.size())
					_current_scene_id - id;
				else
					Core::log::report(ERROR, "Scenes Manager : trying to switch to unknown scene id (%d)", id);
			}

			~SceneManager() = default;

		private:
			std::vector<class Scene*> _scenes;
			int32_t _current_scene_id = -1;
	};
}

#endif
