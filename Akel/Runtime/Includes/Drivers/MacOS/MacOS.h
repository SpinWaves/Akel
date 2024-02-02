// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 03/02/2024

#ifndef __AK_MACOS__
#define __AK_MACOS__

#include <Core/CompilationProfile.h>

#ifndef AK_MACOS_STATIC
	#ifdef AK_PLAT_WINDOWS
		#ifdef AK_COMPILER_MSVC
			#ifdef AK_MACOS_BUILD
				#define AK_MACOS_API __declspec(dllexport)
			#else
				#define AK_MACOS_API __declspec(dllimport)
			#endif
		#elif defined(AK_COMPILER_GCC)
			#ifdef AK_MACOS_BUILD
				#define AK_MACOS_API __attribute__((dllexport))
			#else
				#define AK_MACOS_API __attribute__((dllimport))
			#endif
		#else
			#define AK_MACOS_API
		#endif
	#elif defined(AK_COMPILER_GCC)
		#define AK_MACOS_API __attribute__((visibility("default")))
	#else
		#define AK_MACOS_API
	#endif
#else
	#define AK_MACOS_API
#endif

#endif
