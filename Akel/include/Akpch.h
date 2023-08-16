// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 16/08/2023

#ifndef __AK_PCH__
#define __AK_PCH__

#include <Core/profile.h>

// SDL2
#include <SDL2/SDL.h>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>

// Audio
#include <dr/dr_flac.h>
#include <dr/dr_mp3.h>
#include <dr/dr_wav.h>

// Vulkan
#include <volk.h>
#include <SDL2/SDL_vulkan.h>

// Model loaders
#include <tiny_obj_loader.h>

// JSON/BSON
#include <nlohmann/json.hpp>

// Stb
#include <stb/stb_image.h>

// Spir-V
#include <spirv_reflect.h>

// Entt
#include <entt/entt.hpp>

// PFD
#include <pfd/portable-file-dialogs.h>

// ImGui
#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_vulkan.h>

// Lua
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

// APIs' maths
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

// System
#include <filesystem>
#include <chrono>
#include <algorithm>

#ifdef AK_PLATFORM_WINDOWS
    #include <windows.h>
	#include <shellapi.h>
	#undef max
	#undef min
	#undef ERROR
#endif

// NZSL
#include <NZSL/Parser.hpp>
#include <NZSL/SpirvWriter.hpp>
#include <NZSL/FilesystemModuleResolver.hpp>

// MultiThreading
#include <thread>
#include <mutex>
#include <atomic>
#include <future>

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
#include <queue>
#include <stack>

// Streams
#include <iostream>
#include <fstream>
#include <sstream>
#include <zip/zip.h>

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
#include <limits>

#ifndef M_PI
    #define M_PI 3.141592653589793
#endif

#undef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

constexpr const int MAX_FRAMES_IN_FLIGHT = 3;
constexpr const int MAX_RENDER_TARGETS = 8;
constexpr const int SINGLE_TIME_CMD_RESERVE = 8;

#endif // __AK_PCH__
