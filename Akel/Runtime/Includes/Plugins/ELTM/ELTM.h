// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_ELTM_H
#define AK_ELTM_H

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
