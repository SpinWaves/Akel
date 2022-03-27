// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/04/2021
// Updated : 26/03/2022

#ifndef __AK_UTILS__
#define __AK_UTILS__

/* shortcuts for variable types */
using Ak_uint = unsigned int;
using Ak_ulong = unsigned long;
using Ak_ulonglong = unsigned long long;
using Ak_ushort = unsigned short;
using Ak_ubyte = unsigned char;
using Ak_uchar = unsigned char;
using Ak_text = const char*;
using Ak_byte = char;

#include <Utils/consoleOut.h>
#include <Utils/fps.h>
#include <Utils/camera.h>
#include <Utils/time.h>
#include <Utils/platformUtils.h>
#include <Utils/mStrings.h>
#include <Utils/fStrings.h>
#include <Utils/nonCopyable.h>

#include <Utils/Containers/containers.h>

namespace Ak
{
	template <class T>
	struct default_t // default type class
	{
		static T get() { return T(); }
	};
}

#endif // __AK_UTILS__
