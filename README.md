# Akel
<p align="center">
    <img src="https://raw.githubusercontent.com/SpinWaves/Akel/main/Resources/assets/logo.png" alt="drawing" width="500"/>
</p>

Akel is a game engine made for fun by a young french man.
Currently at an early stage, it is still in development and needs more work to turn it into something.
An editor (like Unity or UnrealEngine) is in development, facilitating the creation of games. However, it will be necessary to wait for some time until this one is sufficiently developed (as well as the engine itself) to make games easily.
Akel is designed to be easy to use. Not being the most powerful, it goes the way of simplicity of use, both on the editor side and on the code side.

# Getting started
Developed mainly on Linux, Akel is, however, cross-platform and can be used on Windows, (no information about MacOS, I have to test it). It is used with [xmake](https://xmake.io/#/). A compiler that supports C++17 is required. Dependencies are provided (SDL2, ImGui, ...) by xmake (you may install Vulkan SDK yourself for debuging).

* Start by clonning the repo `git clone https://github.com/SpinWaves/Akel`
* [Install xmake](https://xmake.io/#/guide/installation)
* <details> <summary>Run xmake in the "xmake.lua" directory</summary>
  By default xmake will only build Akel. If you want to build Akel Studio or one of the demos you can run xmake as follows :

  Demo | Command
  ---- | -------
  Ake Studio | `xmake build Akel_Studio`
  Rectangle | `xmake build RectDemo`
  Cube | `xmake build CubeDemo`
  </details>

# Akel useful features
* Rendering system using Vulkan
* Text management language [ELTM](https://github.com/SpinWaves/Akel/tree/main/Akel/include/Modules/ELTM)
* Efficient error management system
* Memory manager using custom allocators
* Memory protection system in case of crash
* Native ImGui implementation using Akel's renderer
* Native [NZSL](https://github.com/NazaraEngine/ShaderLang) support with helper modules

# Coming soon...
* Custom strings to replace std::string
* Custom shading language
* Models manager
* Resources manager

# Contribute
You can contribute by :
* Reporting problems
* Suggesting features
* [Fork the project](https://github.com/SpinWaves/Akel/fork) on GitHub and push your changes
* Talking about Akel to other people

## Links
[Website](https://akel-engine.com)

[Documentation](https://doc.akel-engine.com)

### Contact
[Profile](https://solo.to/kbz_8)

kbz_8.dev@akel-engine.com
