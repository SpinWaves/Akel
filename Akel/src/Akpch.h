// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 06/04/2022

#ifndef __AK_PCH__
#define __AK_PCH__

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>

// SndFile
#include <sndfile.h>

// Vulkan
#include <vulkan/vulkan.h>
#include <SDL2/SDL_vulkan.h>

// SPIR-V
#include <shaderc/shaderc.hpp>

// ImGui
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_vulkan.h>

// APIs' maths
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// System
#include <filesystem>
#include <chrono>
#include <algorithm>

// MultiThreading
#include <thread>
#include <mutex>

#ifdef AK_PLATFORM_WINDOWS
    #include <windows.h>
#endif

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

#ifndef M_PI
    #define M_PI 3.141592653589793
#endif

#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])

#endif // __AK_PCH__
