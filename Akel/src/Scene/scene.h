// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/11/2022
// Updated : 06/12/2022

#ifndef __AK_SCENE__
#define __AK_SCENE__

#include <Akpch.h>
#include <Platform/input.h>
#include <Utils/fStrings.h>
#include <Graphics/entity.h>

namespace Ak
{
	class Scene
	{
		public:
			Scene(fString name = "Empty scene");

			void onAttach(uint32_t id);
			void onRender3D();
			void onRender2D();
			void onQuit();

			void add_2D_entity(Entity2D entity);

			~Scene() = default;

		private:
			std::vector<class Entity3D> _3D_entities;
			std::vector<class Entity2D> _2D_entities;
			fString _name;
			uint32_t _id = -1;
	};
}

#endif
