// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/04/2021
// Updated : 03/06/2023

#ifndef __AK_UTILS__
#define __AK_UTILS__

using Ak_ui = unsigned int;
using Ak_ul = unsigned long;
using Ak_ull = unsigned long long;
using Ak_us = unsigned short;
using Ak_ub = unsigned char;
using Ak_uc = unsigned char;

using Ak_text = const char*;
using Ak_byte = char;

using Ak_u64 = uint64_t;
using Ak_i64 = int64_t;
using Ak_u32 = uint32_t;
using Ak_i32 = int32_t;
using Ak_u16 = uint16_t;
using Ak_i16 = int16_t;
using Ak_u8 = uint8_t;
using Ak_i8 = int8_t;

using Ak_f32 = float;
using Ak_f64 = double;
using Ak_f96 = long double;

#include <Utils/imguiRenderStatistics.h>
#include <Utils/consoleOut.h>
#include <Utils/ticks.h>
#include <Utils/time.h>
#include <Utils/mStrings.h>
#include <Utils/fStrings.h>
#include <Utils/nonCopyable.h>
#include <Utils/scopeTimer.h>
#include <Utils/selfInstance.h>
#include <Utils/plainApplication.h>
#include <Utils/assert.h>
#include <Utils/hash_combine.h>

#include <Utils/Containers/containers.h>

#include <Core/profile.h>

namespace Ak
{
	/**
	 * Default type class
	 * give the default value of a type
	 * given by template
	 * 
	 * Usage :
	 * 		Myclass my_obj = Ak::default_t<Myclass>::get()
	 */
	template <class T>
	struct AK_API default_t
	{
		static T get() { return T(); }
	};

	template<class... Ts>
	struct AK_API overloaded : Ts...
	{
		using Ts::operator()...;
	};

	template<class... Ts>
	overloaded(Ts...) -> overloaded<Ts...>;
}

#endif // __AK_UTILS__
