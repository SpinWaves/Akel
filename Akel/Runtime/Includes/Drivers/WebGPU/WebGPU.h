// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

#ifndef __AK_WEBGPU__
#define __AK_WEBGPU__

#include <Core/CompilationProfile.h>

#ifndef AK_WEBGPU_STATIC
	#ifdef AK_PLAT_WINDOWS
		#ifdef AK_COMPILER_MSVC
			#ifdef AK_WEBGPU_BUILD
				#define AK_WEBGPU_API __declspec(dllexport)
			#else
				#define AK_WEBGPU_API __declspec(dllimport)
			#endif
		#elif defined(AK_COMPILER_GCC)
			#ifdef AK_WEBGPU_BUILD
				#define AK_WEBGPU_API __attribute__((dllexport))
			#else
				#define AK_WEBGPU_API __attribute__((dllimport))
			#endif
		#else
			#define AK_WEBGPU_API
		#endif
	#elif defined(AK_COMPILER_GCC)
		#define AK_WEBGPU_API __attribute__((visibility("default")))
	#else
		#define AK_WEBGPU_API
	#endif
#else
	#define AK_WEBGPU_API
#endif

#endif
