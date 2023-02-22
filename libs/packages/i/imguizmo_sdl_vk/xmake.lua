-- This file is a part of Akel
-- Author : @kbz_8
-- Created : 08/08/2022
-- Updated : 08/08/2022

package("imguizmo_sdl_vk")

    add_urls("https://github.com/CedricGuillemet/ImGuizmo.git")
    add_versions("1.83", "14a91c16e40b585fd96314826fa6d506311dbe5c")

    add_deps("imgui_sdl_vk v1.89-docking")

    on_install("macosx", "linux", "windows", "mingw", "android", "iphoneos", function(package)
            local xmake_lua = ([[
                add_rules("mode.debug", "mode.release")
                set_languages("c++14")
                add_requires("imgui_sdl_vk v1.87-docking")
                target("imguizmo_sdl_vk")
                    set_kind("static")
                    add_files("*.cpp")
                    add_headerfiles("*.h")
                    add_packages("imgui_sdl_vk")
            ]])
            io.writefile("xmake.lua", xmake_lua)
            import("package.tools.xmake").install(package)
        end)
