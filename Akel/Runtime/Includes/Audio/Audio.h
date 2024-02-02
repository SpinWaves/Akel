// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 02/02/2024

#ifndef __AK_AUDIO__
#define __AK_AUDIO__

#include <Core/CompilationProfile.h>

#ifndef AK_AUDIO_STATIC
	#ifdef AK_PLAT_WINDOWS
		#ifdef AK_COMPILER_MSVC
			#ifdef AK_AUDIO_BUILD
				#define AK_AUDIO_API __declspec(dllexport)
			#else
				#define AK_AUDIO_API __declspec(dllimport)
			#endif
		#elif defined(AK_COMPILER_GCC)
			#ifdef AK_AUDIO_BUILD
				#define AK_AUDIO_API __attribute__((dllexport))
			#else
				#define AK_AUDIO_API __attribute__((dllimport))
			#endif
		#else
			#define AK_AUDIO_API
		#endif
	#elif defined(AK_COMPILER_GCC)
		#define AK_AUDIO_API __attribute__((visibility("default")))
	#else
		#define AK_AUDIO_API
	#endif
#else
	#define AK_AUDIO_API
#endif

#endif
