// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 21/08/2022

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Platform/input.h>
#include <Core/Components/components.h>
#include <Utils/fps.h>
#include <Utils/nonCopyable.h>

namespace Ak
{
	class Application : public ComponentStack, public non_copyable
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
}

#endif // __AK_APPLICATION__
