// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/11/2022
// Updated : 06/12/2022

#ifndef __AK_SCENE_MANAGER__
#define __AK_SCENE_MANAGER__

#include <Akpch.h>
#include <Core/Components/baseComponent.h>
#include <Core/log.h>
#include "scene.h"

namespace Ak
{
	class SceneManager : public Component
	{
		public:
			SceneManager();

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

			inline void remove_scene(class Scene* scene)
			{
				auto it = std::find(_scenes.begin(), _scenes.end(), scene);
				if(it == _scenes.end())
					return;
				(*it)->onQuit();
				_scenes.erase(it);
			}

			inline void remove_scene(uint32_t id)
			{
				if(id > _scenes.size())
					return;
				_scenes[id]->onQuit();
				_scenes.erase(_scenes.begin() + id);
			}

			inline void switch_to_scene(uint32_t id) noexcept
			{
				if(id > _scenes.size())
					Core::log::report(ERROR, "Scenes Manager : trying to switch to unknown scene id (%d)", id);
				else
					_current_scene_id = id;
			}

			~SceneManager() = default;

		private:
			std::vector<class Scene*> _scenes;
			int32_t _current_scene_id = -1;
	};
}

#endif
