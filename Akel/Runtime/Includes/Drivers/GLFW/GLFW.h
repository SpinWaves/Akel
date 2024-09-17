// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_GLFW__
#define __AK_GLFW__

#include <Core/CompilationProfile.h>

#ifndef AK_GLFW_STATIC
	#ifdef AK_PLAT_WINDOWS
		#ifdef AK_COMPILER_MSVC
			#ifdef AK_GLFW_BUILD
				#define AK_GLFW_API __declspec(dllexport)
			#else
				#define AK_GLFW_API __declspec(dllimport)
			#endif
		#elif defined(AK_COMPILER_GCC)
			#ifdef AK_GLFW_BUILD
				#define AK_GLFW_API __attribute__((dllexport))
			#else
				#define AK_GLFW_API __attribute__((dllimport))
			#endif
		#else
			#define AK_GLFW_API
		#endif
	#elif defined(AK_COMPILER_GCC)
		#define AK_GLFW_API __attribute__((visibility("default")))
	#else
		#define AK_GLFW_API
	#endif
#else
	#define AK_GLFW_API
#endif

#endif
