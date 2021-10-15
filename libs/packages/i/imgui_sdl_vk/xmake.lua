package("imgui_sdl_vk")

    set_homepage("https://github.com/ocornut/imgui")
    set_description("Bloat-free Immediate Mode Graphical User interface for C++ with minimal dependencies")

    add_urls("https://github.com/ocornut/imgui/archive/$(version).tar.gz",
             "https://github.com/ocornut/imgui.git")
    add_versions("v1.84.2", "35cb5ca0fb42cb77604d4f908553f6ef3346ceec4fcd0189675bdfb764f62b9b")
    add_versions("v1.84.1", "292ab54cfc328c80d63a3315a242a4785d7c1cf7689fbb3d70da39b34db071ea")
    add_versions("v1.83-docking", "80b5fb51edba2fd3dea76ec3e88153e2492243d1")
    add_versions("v1.83", "ccf3e54b8d1fa30dd35682fc4f50f5d2fe340b8e29e08de71287d0452d8cc3ff")
    add_versions("v1.82", "fefa2804bd55f3d25b134af08c0e1f86d4d059ac94cef3ee7bd21e2f194e5ce5")
    add_versions("v1.81", "f7c619e03a06c0f25e8f47262dbc32d61fd033d2c91796812bf0f8c94fca78fb")
    add_versions("v1.80", "d7e4e1c7233409018437a646680316040e6977b9a635c02da93d172baad94ce9")
    add_versions("v1.79", "f1908501f6dc6db8a4d572c29259847f6f882684b10488d3a8d2da31744cd0a4")
    add_versions("v1.75", "1023227fae4cf9c8032f56afcaea8902e9bfaad6d9094d6e48fb8f3903c7b866")

    add_includedirs("include", "include/imgui")

    if is_plat("windows", "mingw") then
        add_syslinks("Imm32")
    end

    on_load("macosx", "linux", "windows", "mingw", "android", "iphoneos", function(package)
        package:add("deps", "libsdl", "vulkan-headers", "vulkan-loader", "vulkan-tools")

        if package:version_str():find("-docking", 1, true) then
            package:set("urls", {"https://github.com/ocornut/imgui.git"})
        end
    end)

    on_install("macosx", "linux", "windows", "mingw", "android", "iphoneos", function(package, target)
        local configs = {}
        configs.kind = "shared"
        local xmake_lua
        local pkgs = "\"libsdl\", \"vulkan-headers\", \"vulkan-loader\", \"vulkan-tools\""
        xmake_lua = format([[
            add_rules("mode.debug", "mode.release")
            add_rules("utils.install.cmake_importfiles")
            add_requires(%s)
            target("imgui_sdl_vk")
                set_kind("shared")
                add_files("*.cpp", "backends/imgui_impl_sdl.cpp", "backends/imgui_impl_vulkan.cpp")
                add_packages(%s)
                add_includedirs(".")
                add_headerfiles("*.h", {prefixdir = "imgui"})
                add_headerfiles("backends/imgui_impl_sdl.h", "backends/imgui_impl_vulkan.h")
        ]], pkgs, pkgs)

        io.writefile("xmake.lua", xmake_lua)
        import("package.tools.xmake").install(package, configs)
        os.cp(path.join(package:installdir(), "lib"), path.join(os.scriptdir(), "install"))
    end)
 