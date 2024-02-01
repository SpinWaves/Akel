// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 01/02/2024

#ifndef __AK_CORE_BASE_EVENT__
#define __AK_CORE_BASE_EVENT__

#include <Core/PreCompiled.h>

namespace Ak
{
	struct EventBase
	{
		virtual std::uint32_t What() const = 0;
	};
}

#endif
