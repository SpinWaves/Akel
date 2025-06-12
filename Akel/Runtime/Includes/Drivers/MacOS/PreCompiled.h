// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_DRIVERS_MACOS_PRE_COMPILED_HEADER_H
#define AK_DRIVERS_MACOS_PRE_COMPILED_HEADER_H

#include <Core/CompilationProfile.h>
#include <Drivers/MacOS/MacOS.h>

#ifdef AK_PLAT_MACOS
	#include <mach-o/dyld.h>
	#include <dlfcn.h>
#endif

#endif
