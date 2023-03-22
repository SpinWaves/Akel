// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/03/2023
// Updated : 22/03/2023

#ifndef __AK_SCRIPT__
#define __AK_SCRIPT__

#include <Akpch.h>

namespace Ak
{
	class AK_API Script
	{
		public:
			Script() = default;

			virtual void runOnInit() = 0;
			virtual void runOnUpdate(float delta) = 0;
			virtual void runOnQuit() = 0;

			virtual ~Script() = default;
	};
}

#endif
