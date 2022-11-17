// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/11/2022
// Updated : 17/11/2022

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
			void onAttach(Input& in) override;
			void onRender() override;
			void onQuit() override;

			void add_scene(class Scene* scene);
			void remove_scene(class Scene* scene);
			void remove_scene(uint32_t id);

			~SceneManager() = default;

		private:
			std::vector<class Scene*> _scenes;
	};
}

#endif
