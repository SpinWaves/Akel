// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 06/02/2024

#ifndef __AK_CORE_MODULE__
#define __AK_CORE_MODULE__

#include <Utils/NonMovable.h>
#include <Utils/NonCopyable.h>
#include <Core/PreCompiled.h>

namespace Ak
{
	class Module : public NonCopyable, NonMovable
	{
		public:
			virtual ~Module();

		protected:
			Module(std::string name);

		private:
			std::string m_module_name;
	};
}

#endif
