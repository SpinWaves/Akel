// This file is a part of Akel
// CREATED : 26/06/2021
// UPDATED : 27/06/2021

#ifndef __AK_PROFILE_CORE__
#define __AK_PROFILE_CORE__

#define AK_PROFILE 0
#if AK_PROFILE
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
#else
	#define AK_FUNC_SIG __FUNCTION__
#endif

#endif // __AK_PROFILE_CORE__

