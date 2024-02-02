// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 03/02/2024

#ifndef __AK_UNIX__
#define __AK_UNIX__

#include <Core/CompilationProfile.h>

#ifndef AK_UNIX_STATIC
	#ifdef AK_PLAT_WINDOWS
		#ifdef AK_COMPILER_MSVC
			#ifdef AK_UNIX_BUILD
				#define AK_UNIX_API __declspec(dllexport)
			#else
				#define AK_UNIX_API __declspec(dllimport)
			#endif
		#elif defined(AK_COMPILER_GCC)
			#ifdef AK_UNIX_BUILD
				#define AK_UNIX_API __attribute__((dllexport))
			#else
				#define AK_UNIX_API __attribute__((dllimport))
			#endif
		#else
			#define AK_UNIX_API
		#endif
	#elif defined(AK_COMPILER_GCC)
		#define AK_UNIX_API __attribute__((visibility("default")))
	#else
		#define AK_UNIX_API
	#endif
#else
	#define AK_UNIX_API
#endif

#endif
