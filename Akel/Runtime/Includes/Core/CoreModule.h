// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#ifndef __AK_CORE_COREMODULE__
#define __AK_CORE_COREMODULE__

#include <Core/PreCompiled.h>
#include <Core/Module.h>

namespace Ak
{
	class AK_CORE_API CoreModule : public Module<CoreModule>
	{
		friend Module;

		public:
			CoreModule();
			~CoreModule();

		private:
			static CoreModule* s_instance;
	};
}

#endif
