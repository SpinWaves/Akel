// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_BASE_EVENT_H
#define AK_CORE_BASE_EVENT_H

#include <Core/PreCompiled.h>

namespace Ak
{
	struct EventBase
	{
		virtual std::uint32_t What() const = 0;
	};
}

#endif
