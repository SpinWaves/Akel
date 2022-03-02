// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/06/2021
// Updated : 23/02/2022

#ifndef __AK_PROFILE_CORE__
#define __AK_PROFILE_CORE__

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define AK_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define AK_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
	#define AK_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define AK_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define AK_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define AK_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define AK_FUNC_SIG __func__
#else
	#define AK_FUNC_SIG "Unknown function"
#endif

#if defined(_WIN32) || defined(_WIN64)
	#define AK_PLATFORM_WINDOWS
	#define forceinline __forceinline
	#if _WIN64
		#define AK_64BITS
	#else
		#define AK_32BITS
	#endif
#elif __GNUC__
	#if __x86_64__ || __ppc64__
		#define AK_64BITS
	#else
		#define AK_32BITS
	#endif
#endif

#if defined(__x86_64__) || defined(_M_X64)
	#define AK_x86_64
	#ifndef AK_64BITS
		#define AK_64BITS
	#endif
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
	#define AK_x86_32
	#ifndef AK_32BITS
		#define AK_32BITS
	#endif
#elif defined(__ARM_ARCH_2__)
	#define AK_ARM2
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
	#define AK_ARM3
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
	#define AK_ARM4T
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
	#define AK_ARM5
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
	#define AK_ARM6T2
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
	#define AK_ARM6
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
	#define AK_ARM7
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
	#define AK_ARM7A
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
	#define AK_ARM7R
#elif defined(__ARM_ARCH_7M__)
	#define AK_ARM7M
#elif defined(__ARM_ARCH_7S__)
	#define AK_ARM7S
#elif defined(__aarch64__) || defined(_M_ARM64)
	#define AK_ARM64
#elif defined(mips) || defined(__mips__) || defined(__mips)
	#define AK_MIPS
#elif defined(__sh__)
	#define AK_SUPERH
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
	#define AK_POWERPC
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
	#define AK_POWERPC64
#elif defined(__sparc__) || defined(__sparc)
	#define AK_SPARC
#elif defined(__m68k__)
	#define AK_M68K
#endif

#if !defined(AK_32BITS) && !defined(AK_64BITS)
	#error Akel can only run on 32bit or 64bit architectures
#endif

#ifdef __linux__
	#define AK_PLATFORM_LINUX
	#define forceinline __attribute__((always_inline))
#elif defined(__APPLE__) || defined(__MACH__)
	#define AK_PLATFORM_OSX
	#define forceinline __attribute__((always_inline))
#endif

#endif // __AK_PROFILE_CORE__
