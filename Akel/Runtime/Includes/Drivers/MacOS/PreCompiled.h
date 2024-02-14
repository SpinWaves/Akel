// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 13/02/2024

#ifndef __AK_DRIVERS_MACOS_PRE_COMPILED_HEADER__
#define __AK_DRIVERS_MACOS_PRE_COMPILED_HEADER__

#include <Core/CompilationProfile.h>
#include <Drivers/MacOS/MacOS.h>

#ifdef AK_PLAT_MACOS
	#include <mach-o/dyld.h>
	#include <dlfcn.h>
#endif

#endif
