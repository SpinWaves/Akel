// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/03/2023
// Updated : 25/03/2023

#ifndef __AK_SCRIPT__
#define __AK_SCRIPT__

#include <Akpch.h>
#include <Scene/entity.h>

namespace Ak
{
	class AK_API Script
	{
		public:
			Script() = default;

			virtual void runOnInit(Entity* this_entity) = 0;
			virtual void runOnUpdate(Entity* this_entity, float delta) = 0;
			virtual void runOnQuit(Entity* this_entity) = 0;

			virtual ~Script() = default;
	};
}

#endif
