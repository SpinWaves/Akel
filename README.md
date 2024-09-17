# Akel

[![linux workflow](https://github.com/SpinWaves/Akel/actions/workflows/linux-build.yml/badge.svg)](https://github.com/SpinWaves/Akel/actions/workflows/linux-build.yml)
[![windows workflow](https://github.com/SpinWaves/Akel/actions/workflows/windows-build.yml/badge.svg)](https://github.com/SpinWaves/Akel/actions/workflows/windows-build.yml)
[![macos workflow](https://github.com/SpinWaves/Akel/actions/workflows/macos-build.yml/badge.svg)](https://github.com/SpinWaves/Akel/actions/workflows/macos-build.yml)
[![wasm workflow](https://github.com/SpinWaves/Akel/actions/workflows/wasm-build.yml/badge.svg)](https://github.com/SpinWaves/Akel/actions/workflows/wasm-build.yml)
[![minGW workflow](https://github.com/SpinWaves/Akel/actions/workflows/msys2-build.yml/badge.svg)](https://github.com/SpinWaves/Akel/actions/workflows/msys2-build.yml)

<p align="center">
    <img src="https://raw.githubusercontent.com/SpinWaves/Akel/main/Resources/assets/logo.png" alt="drawing" width="500"/>
</p>

Akel is a game engine made for fun, highly inspired by [Nazara](https://github.com/NazaraEngine/NazaraEngine) on some points.
Currently at an early stage, it is still in development and needs more work to turn it into something.
An editor is in development, facilitating the creation of games. However, it will be necessary to wait for some time until this one is sufficiently developed (as well as the engine itself) to make games easily.
Akel is designed to be easy to use. Not being the most powerful, it goes the way of simplicity both on the editor side and on the engine side.

# Getting started
Developed mainly on Linux, Akel is, however, cross-platform and can be used on Windows and MacOS. It is compiled using [xmake](https://xmake.io/#/). A compiler that supports C++17 is required. Dependencies (SDL2, ImGui, ...) are provided by xmake (you may install Vulkan SDK yourself for debuging).

* Start by clonning the repo `git clone https://github.com/SpinWaves/Akel`
* [Install xmake](https://xmake.io/#/guide/installation)
* Run xmake in the "xmake.lua" directory

# Akel useful features
* Rendering system using Vulkan
* Text management language [ELTM](https://github.com/SpinWaves/Akel/tree/main/Akel/include/Modules/ELTM)
* Efficient error management system
* Memory manager using custom allocators
* Memory protection system in case of fatal error
* Native ImGui implementation using Akel's renderer
* Native [NZSL](https://github.com/NazaraEngine/ShaderLang) support with helper modules
* Native scripting using Lua
* Easy integration of other scripting languages

# Screenshots
<p align="center">
    <img src="https://raw.githubusercontent.com/SpinWaves/Akel/main/Resources/screenshots/akel_studio.png" alt="drawing"/>
</p>

<p align="center">
    <img src="https://raw.githubusercontent.com/SpinWaves/Akel/main/Resources/screenshots/Screenshot_model_demo.png" alt="drawing"/>
</p>

# Contribute
You can contribute by :
* Reporting issues
* Suggesting features
* Making pull requests
* Talking about Akel to other people

## Links
[Website](https://akel-engine.com)

### Contact
[Profile](https://solo.to/kbz_8)

kbz_8.dev@akel-engine.com
