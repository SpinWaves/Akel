# AtlasEngine

![Logo](https://github.com/Kbz-8/AtlasEngine/blob/30a865d55a1d5b173c88ff1e9d123dffbe5313b8/src/assets/logo.png)

AtlasEngine is a game engine made for fun by a young french man.
Currently at an early stage, it is still in development and still needs some work to turn it into something.
A graphical interface (like Unity or UnrealEngine) will soon be in development, facilitating the creation of games. However, it will be necessary to wait for some time until this one is sufficiently developed (as well as the engine itself) to make games "easily".

# Getting started
Developed mainly on Linux, AtlasEngine is, however, cross-platform and can be used on Windows, although it has not been tested on this OS (no information about MacOS, I have to find out). It is used with Premake5. GCC 9 is required because it uses C++17 features. Dependencies are provided (SDL2, OpenGL, Vulkan, GML) with the code.

* Start by clonning the repo in your project's folder `git clone https://github.com.Kbz-8/AtlasEngine`.
* <details> <summary>Create a "premake5.lua" file in your project's directory, here's an example of what it might look like if your AtlasEnigne folder is in the same directory as your premake5.lua file: </summary>
```lua
include "./AtlasEngine/vendor/premake/premake_customization/solution_items.lua"

workspace "test"
  startproject "AtlasEngine"
  startproject "engineTester"

  configurations
  {
    "Debug",
    "Release"
  }

  solution_items ".editorconfig"

  flags "MultiProcessorCompile"
  outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "AtlasEngine"

project "engineTester"
  kind "WindowedApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"
  icon "%{prj.location}/AtlasEngine/src/assets/logo.png"

  targetdir ("%{prj.location}")
  objdir ("%{prj.location}/bin-int/" .. outputdir)

  files "test.cpp"

  libdirs "./AtlasEngine/build/Debug-linux-"
  links "AtlasEngine"

  includedirs 
  {
    "%{prj.location}/AtlasEngine/src",
    "%{prj.location}/AtlasEngine/libs/include"
  }
  ```
   </details>
