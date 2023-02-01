// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 31/01/2023

#ifndef __AK_PCH__
#define __AK_PCH__

// SDL2
#include <SDL2/SDL.h>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>

// SndFile
#include <sndfile.h>

// Vulkan
#include <volk.h>
#include <SDL2/SDL_vulkan.h>
#include <vk_mem_alloc.h>

// JSON/BSON
#include <nlohmann/json.hpp>

// Spir-V
#include <spirv_reflect.h>

// Entt
#include <entt/entt.hpp>

// ImGui
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_vulkan.h>

// Lua
#include <sol/sol.hpp>

// APIs' maths
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// System
#include <filesystem>
#include <chrono>
#include <algorithm>

#ifdef AK_PLATFORM_WINDOWS
    #include <windows.h>
	#include <shellapi.h>
#endif

// MultiThreading
#include <thread>
#include <mutex>
#include <atomic>

// Memory
#include <memory>
#include <initializer_list>
#include <any>
#include <type_traits>
#include <tuple>
#include <new>

// Containers
#include <optional>
#include <set>
#include <unordered_map>
#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <array>
#include <variant>
#include <deque>
#include <stack>

// Streams
#include <iostream>
#include <fstream>
#include <sstream>

// C-libs
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <cstddef>
#include <climits>

// Other includes
#include <exception>
#include <function/function.h>
#include <iterator>
#include <iomanip>
#include <numeric>

#ifndef M_PI
    #define M_PI 3.141592653589793
#endif

#undef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

constexpr const int MAX_FRAMES_IN_FLIGHT = 2;

#endif // __AK_PCH__
