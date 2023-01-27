// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 27/01/2023

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Platform/input.h>
#include <Core/Components/components.h>
#include <Utils/fps.h>
#include <Utils/nonCopyable.h>
#include "projectFile.h"
#include <Core/profile.h>

namespace Ak
{
	class AK_API Application : public ComponentStack, public non_copyable
	{
		public:
			Application();
			void run();
			void end();
			void destroy();
			~Application();

		private:
			Input _in;
			CounterFPS _fps;
			inline static bool _app_check = false;
	};

	ComponentStack* getMainAppComponentStack();
}

#endif // __AK_APPLICATION__
