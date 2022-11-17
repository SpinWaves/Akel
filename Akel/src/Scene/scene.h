// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 17/11/2022

#ifndef __AK_SCENE__
#define __AK_SCENE__

#include <Akpch.h>
#include <Platform/input.h>

namespace Ak
{
	class Scene
	{
		public:
			Scene();

			virtual void onAttach(uint32_t id) {}
			virtual void update() {}
			virtual void onEvent(Input& in) {}
			virtual void onRender3D() {}
			virtual void onRender2D() {}
			virtual void onQuit() {}

			~Scene();

		private:
			std::string _name = "Empty scene";
			uint32_t _id = -1;
	};
}

#endif
