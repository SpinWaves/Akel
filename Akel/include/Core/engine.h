// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/09/2023
// Updated : 10/09/2023

#ifndef __AK_ENGINE__
#define __AK_ENGINE__

#include <Akpch.h>
#include <Core/application.h>
#include <Core/instance.h>
#include <Core/Memory/akel_unique_ptr.h>

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
			void fatalErrorEventHandle();

		private:
			Application _app;
			AkelInstance _instance;
	};
}

#endif
