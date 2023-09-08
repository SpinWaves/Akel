// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/09/2023
// Updated : 08/09/2023

#ifndef __AK_ENGINE__
#define __AK_ENGINE__

#include <Akpch.h>

namespace Ak
{
	class AK_API Engine
	{
		public:
			Engine() = default;
			void init(int ac, char** av);
			void run();
			void destroy();
			~Engine() = default;

		private:
			Application _app;
			AkelInstance _instance;
	};
}

#endif
