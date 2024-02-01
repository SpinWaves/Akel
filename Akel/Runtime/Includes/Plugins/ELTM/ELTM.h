// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/05/2021
// Updated : 01/02/2024

#ifndef __AK_ELTM__
#define __AK_ELTM__

#include <Core/CompilationProfile.h>

#ifndef AK_ELTM_STATIC
	#ifdef AK_PLAT_WINDOWS
		#ifdef AK_COMPILER_MSVC
			#ifdef AK_ELTM_BUILD
				#define AK_ELTM_API __declspec(dllexport)
			#else
				#define AK_ELTM_API __declspec(dllimport)
			#endif
		#elif defined(AK_COMPILER_GCC)
			#ifdef AK_ELTM_BUILD
				#define AK_ELTM_API __attribute__((dllexport))
			#else
				#define AK_ELTM_API __attribute__((dllimport))
			#endif
		#else
			#define AK_ELTM_API
		#endif
	#elif defined(AK_COMPILER_GCC)
		#define AK_ELTM_API __attribute__((visibility("default")))
	#else
		#define AK_ELTM_API
	#endif
#else
	#define AK_ELTM_API
#endif

#endif
