// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#ifndef __AK_CORE_MODULE__
#define __AK_CORE_MODULE__

#include <Core/PreCompiled.h>

namespace Ak
{
	template <typename T>
	class AK_CORE_API Module
	{
		friend class CoreModule;

		public:
			Module(const Module&) = delete;
			Module(Module&&) = delete;

			Module& operator=(const Module&) = delete;
			Module& operator=(Module&&) = delete;

			static inline T* Get();

		protected:
			Module(std::string name, T* ptr);
			virtual ~Module();

		private:
			std::string m_module_name;
	};
}

#endif
