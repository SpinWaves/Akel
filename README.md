# Akel
<p align="center">
    <img src="https://github.com/SpinWaves/Akel/blob/main/Ressources/assets/logo.png" alt="drawing" width="500"/>
</p>

Akel is a game engine made for fun by a young french man.
Currently at an early stage, it is still in development and still needs some work to turn it into something.
An editor (like Unity or UnrealEngine) is in development, facilitating the creation of games. However, it will be necessary to wait for some time until this one is sufficiently developed (as well as the engine itself) to make games easily.
Akel is designed to be extremely easy to use. Not being the most powerful, it goes the way of simplicity of use, both on the editor side and on the code side.

# Getting started
Developed mainly on Linux, Akel is, however, cross-platform and can be used on Windows, although it has not been tested on this OS (no information about MacOS, I have to find out). It is used with [xmake](https://xmake.io/#/). GCC 8(or higher) is required because it uses C++17 features. Dependencies are provided (SDL2, ImGui, Vulkan, GLM) by xmake.

* Start by clonning the repo `git clone https://github.com/SpinWaves/Akel`.
* [Install xmake](https://xmake.io/#/guide/installation) (choose according to your system (Windows, Linux, ...)).
* <details> <summary>Run xmake in the "xmake.lua" directory.</summary>
  By default xmake will build the Akel editor. If you want to build one of the demos you can run xmake as follows :

  Demo | Command
  ---- | -------
  Editor | `xmake` or `xmake build Editor`
  Rectangle | `xmake build RectDemo`
  Cube | Coming soon...

  </details>

# Akel useful features
* Text management language [ELTM](https://github.com/SpinWaves/Akel/tree/main/Akel/src/Modules/ELTM)
* Simple but efficient error management system
* Rendering system with Vulkan
* [2 memory allocation systems](https://github.com/SpinWaves/Akel/tree/main/Akel/src/Core/Memory):
    * FixedAllocator is a fast allocator consisting of blocks of the same size that can be allocated. It is more performance oriented than memory optimised because if an allocated block is not used in full, the unused memory is wasted.
    * JamAllocator is a slightly less efficient (but still effective) allocator that is memory optimisation oriented. It allocates the memory size you want, no memory is wasted.

# Coming soon...
* Fully functionnal renderer using Vulkan API
* Demos
* Custom strings to replace std::string
* Finished ELTM version 1.1 including :
    * Concatenation
    * Recognition of \n and \t
    * Documentation
* Better ImGui component implementation using Akel Vulkan renderer
* Custom shading language
* More powerful allocators
* Entity management
* Models manager

# Contribute
You can contribute by :
* Reporting problems
* Suggesting features
* [Fork the project](https://github.com/SpinWaves/Akel/fork) on GitHub and push your changes
* Talking about Akel to other people

## Links
[Website](https://akel-engine.com)

### Contact
[Profile](https://solo.to/kbz_8)

kbz_8.dev@akel-engine.com
