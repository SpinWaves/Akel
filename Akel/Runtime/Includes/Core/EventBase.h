// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
