// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 05/12/2022

#ifndef __AK_SCENE__
#define __AK_SCENE__

#include <Akpch.h>
#include <Platform/input.h>
#include <Utils/fString.h>

namespace Ak
{
	class Scene
	{
		public:
			Scene(fString name = "Empty scene");

			void onAttach(uint32_t id);
			void update();
			void onEvent(Input& in);
			void onRender3D();
			void onRender2D();
			void onQuit();

			~Scene();

		private:
			fString _name;
			uint32_t _id = -1;
	};
}

#endif
