// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/03/2023
// Updated : 20/03/2023

#ifndef __AK_SCRIPT__
#define __AK_SCRIPT__

#include <Akcph.h>

namespace Ak
{
	class AK_API Script
	{
		friend class ScriptLoader;

		public:
			Script() = default;

			void runOnInit();
			void runOnUpdate(float delta);
			void runOnQuit();

			~Script() = default;

		private:
			std::function<void(void)> _on_init;
			std::function<void(float)> _on_update;
			std::function<void(void)> _on_quit;
	};
}

#endif
