-- This file is a part of Akel
-- Authors : @kbz_8
-- Created : 05/07/2022
-- Updated : 05/07/2022

package("imguizmo_shared")

    add_urls("https://github.com/CedricGuillemet/ImGuizmo.git")
    add_versions("1.83", "14a91c16e40b585fd96314826fa6d506311dbe5c")

    add_deps("imgui_sdl_vk v1.87-docking")

    on_install("macosx", "linux", "windows", "mingw", "android", "iphoneos", function(package)
            local xmake_lua = ([[
                add_rules("mode.debug", "mode.release")
                set_languages("c++14")
                add_requires("imgui_sdl_vk v1.87-docking")
                target("imguizmo_shared")
                    set_kind("shared")
                    add_files("*.cpp")
                    add_headerfiles("*.h")
                    add_packages("imgui_sdl_vk")
            ]])
            io.writefile("xmake.lua", xmake_lua)
            import("package.tools.xmake").install(package)
        end)
