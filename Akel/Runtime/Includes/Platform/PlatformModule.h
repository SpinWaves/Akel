// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 06/02/2024

#ifndef __AK_PLATFORM_MODULE__
#define __AK_PLATFORM_MODULE__

#include <Platform/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>

namespace Ak
{
	class AK_PLATFORM_API PlatformModule : public Module
	{
		public:
			using Dependencies = TypeList<>;

			PlatformModule();

			static PlatformModule& Get();

			~PlatformModule() override;

		private:
			static PlatformModule* s_instance;
	};
}

#endif
