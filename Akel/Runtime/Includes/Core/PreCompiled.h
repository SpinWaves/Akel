// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_PRE_COMPILED_HEADER_H
#define AK_CORE_PRE_COMPILED_HEADER_H

#include <Core/CompilationProfile.h>
#include <Core/Core.h>

#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <memory>
#include <cstdarg>
#include <string>
#include <function/function.h>
#include <fstream>
#include <toml++/toml.h>
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
#include <variant>
#include <unordered_map>

#if !__has_include(<filesystem>)
	#if !__has_include(<experimental/filesystem>)
		#error "include <filesystem> is required to build Akel Engine's Core"
	#else
		#include <experimental/filesystem>
	#endif
#else
	#include <filesystem>
#endif

// Akel core includes
#include <Core/Logs.h>
#include <Core/Memory/MemoryManager.h>
#include <Core/Memory/UniquePtr.h>
#include <Core/Memory/SharedPtr.h>
#include <Core/Memory/WeakPtr.h>

#endif
