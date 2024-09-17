// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_DRIVERS_WINDOWS_PRE_COMPILED_HEADER__
#define __AK_DRIVERS_WINDOWS_PRE_COMPILED_HEADER__

#include <Core/CompilationProfile.h>
#include <Drivers/Windows/Windows.h>

#include <cstdlib>

#ifdef AK_PLAT_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX // For windows.h
	#endif
	#include <windows.h>
	#include <shellapi.h>
	#include <dwmapi.h>
	#include <winuser.h>
#endif

#endif
