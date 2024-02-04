// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 04/02/2024

#ifndef __AK_DRIVERS_WINDOWS_PRE_COMPILED_HEADER__
#define __AK_DRIVERS_WINDOWS_PRE_COMPILED_HEADER__

#include <Core/CompilationProfile.h>
#include <Drivers/Windows/Windows.h>

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
