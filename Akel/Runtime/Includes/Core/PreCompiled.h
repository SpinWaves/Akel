// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 18/02/2024

#ifndef __AK_CORE_PRE_COMPILED_HEADER__
#define __AK_CORE_PRE_COMPILED_HEADER__

#include <Core/CompilationProfile.h>
#include <Core/Core.h>

#include <cstdint>
#include <cstddef>
#include <memory>
#include <cstdarg>
#include <string>
#include <function/function.h>
#include <cassert>
#include <ostream>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <sstream>
#include <vector>
#include <cstring>
#include <type_traits>
#include <mutex>
#include <map>
#include <chrono>
#include <thread>
#include <optional>
#include <unordered_set>

#if !__has_include(<filesystem>)
	#if !__has_include(<experimental/filesystem>)
		#error "include <filesystem> is required to build Akel Engine's Core"
	#else
		#include <experimental/filesystem>
	#endif
#else
	#include <filesystem>
#endif

#endif
