// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 08/02/2024

#ifndef __AK_UTILS_MODULE__
#define __AK_UTILS_MODULE__

#include <Utils/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>

namespace Ak
{
	class AK_UTILS_API UtilsModule : public Module
	{
		public:
			using Dependencies = TypeList<class CoreModule>;

			UtilsModule();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static UtilsModule& Get();

			~UtilsModule() override;

		private:
			static UtilsModule* s_instance;
	};
}

#endif
