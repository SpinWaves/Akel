// This file is a part of Akel
// CREATED : 28/03/2021
// UPDATED : 08/09/2021

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
#include <snd/sndfile.h>

// Vulkan
#include <vulkan/vulkan.h>
#include <SDL2/SDL_vulkan.h>

// ImGui
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl.h>
#include <imgui/backends/imgui_impl_vulkan.h>

// APIs' maths
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// System
#include <filesystem>
#include <chrono>
#include <algorithm>

// MultiThreading
#include <thread>
#include <mutex>

#ifdef Ak_PLATFORM_WINDOWS
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
#include <map>
#include <vector>
#include <array>
#include <variant>

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

// Other includes
#include <exception>

#endif // __AK_PCH__
