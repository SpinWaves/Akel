# Akel
<p align="center">
    <img src="https://github.com/Kbz-8/Akel/blob/main/Ressources/logo.png" alt="drawing" width="500"/>
</p>

Akel is a game engine made for fun by a young french man.
Currently at an early stage, it is still in development and still needs some work to turn it into something.
An editor (like Unity or UnrealEngine) is in development, facilitating the creation of games. However, it will be necessary to wait for some time until this one is sufficiently developed (as well as the engine itself) to make games easily.
Akel is designed to be extremely easy to use. Not being the most powerful, it goes the way of simplicity of use, both on the editor side and on the code side.

# Getting started
Developed mainly on Linux, Akel is, however, cross-platform and can be used on Windows, although it has not been tested on this OS (no information about MacOS, I have to find out). It is used with [Premake5](https://premake.github.io/). GCC 8 is required because it uses C++17 features. Dependencies are provided (SDL2, ImGui, Vulkan, GLM) with the code.

* Start by clonning the repo `git clone --recursive https://github.com.Kbz-8/Akel`.
  If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.
* <details> <summary>Use the "premake5" executable provided in "dependencies/premake/bin" (choose carefully according to your system (Windows, Linux, ...)), then launch it in the main folder with the right option depending on how you compile your it :</summary>

    Premake5 options | Consequences
    ---------------- | ------------
    vs2019 | Generate Visual Studio 2019 project files
    vs2017 | Generate Visual Studio 2017 project files
    vs2015 | Generate Visual Studio 2015 project files
    vs2013 | Generate Visual Studio 2013 project files
    vs2012 | Generate Visual Studio 2012 project files
    vs2010 | Generate Visual Studio 2010 project files
    vs2008 | Generate Visual Studio 2008 project files
    vs2005 | Generate Visual Studio 2005 project files
    gmake  | Generate GNU Makefiles (This generator is deprecated by gmake2)
    gmake2 | Generate GNU Makefiles (including Cygwin and MinGW)
    xcode4 | XCode projects
    codelite | CodeLite projects

</details>

* Build your project and enjoy or cry depending on if it compiles correctly or if there are 400 errors

# Akel useful features
* Text management language [ELTM](https://github.com/Kbz-8/Akel/tree/main/Akel/src/Modules/ELTM)
* Simple but efficient error management system
* Rendering system with Vulkan
* 2 memory allocation systems:
    * FixedAllocator is a fast allocator consisting of blocks of the same size that can be allocated. It is more performance oriented than memory optimised because if an allocated block is not used in full, the unused memory is wasted.
    * JamAllocator is a slightly less efficient (but still effective) allocator that is memory optimisation oriented. It allocates the memory size you want, no memory is wasted.

# Contribute
You can contribute by :
* reporting problems
* suggesting features
* [Fork the project](https://github.com/Kbz-8/Akel/fork) on GitHub and push your changes
* Talking about Akel to other people

## Links
[Website](http://akel-engine.com)

### Contact
bilbo.sacquet@orange.fr
