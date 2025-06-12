// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_MODULE_H
#define AK_CORE_MODULE_H

#include <Utils/NonMovable.h>
#include <Utils/NonCopyable.h>
#include <Core/PreCompiled.h>

namespace Ak
{
	class Module : public NonCopyable, NonMovable
	{
		public:
			virtual ~Module();

			inline const std::string& GetName() const { return m_module_name; }
			virtual void Update() {}

		protected:
			Module(std::string name);

		private:
			std::string m_module_name;
	};
}

#endif
