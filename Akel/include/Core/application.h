// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 06/08/2023

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Platform/input.h>
#include <Core/Components/components.h>
#include <Utils/ticks.h>
#include <Utils/nonCopyable.h>
#include "projectFile.h"
#include <Core/profile.h>

namespace Ak
{
	struct AK_API CommandLineArgs
	{
		char** args = nullptr;
		int count = 0;

		const char* operator[](int index) const noexcept;
	};

	class AK_API Application : public ComponentStack, public non_copyable
	{
		public:
			Application();
			void run();
			inline const Input& getInput() const noexcept { return _in; }
			void end();
			void destroy();
			~Application() = default;

		private:
			Input _in;
			CounterTicks _ticks;
			inline static bool _app_check = false;
	};

	ComponentStack* getMainAppComponentStack();
}

#endif // __AK_APPLICATION__
