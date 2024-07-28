package("kvf")
	set_homepage("https://github.com/Kbz-8/KVF")
	set_description("kvf is a header only Vulkan framework in C99 with no other dependencies than the libc")
	set_license("MIT")

	add_urls("https://github.com/Kbz-8/KVF.git")
	add_deps("vulkan-headers")

	on_install("windows", "linux", "macosx", "mingw", "iphoneos", "android", function(package)
		io.writefile("xmake.lua", [[
			add_requires("vulkan-headers")
			target("kvf")
				set_kind("headeronly")
				add_headerfiles("kvf.h")
				add_packages("vulkan-headers")
		]])
		import("package.tools.xmake").install(package)
	end)

	on_load(function(package)
		if package:config("header_only") then
			package:set("kind", "library", {headeronly = true})
		end
	end)

	on_test(function(package)
		local defines = "KVF_IMPLEMENTATION"

		assert(package:check_csnippets({test = [[
			#include <kvf.h>
			#include <stdlib.h>
			void test()
			{
				VkInstance instance = kvfCreateInstance(NULL, 0);
				kvfDestroyInstance(instance);
			}
		]]}, {configs = {defines = defines}}))
	end)
