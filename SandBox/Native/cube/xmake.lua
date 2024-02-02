target("CubeDemo")
	add_deps("AkelCore", "AkelPlatform", "AkelRenderer", "AkelGraphics")
	if is_plat("linux") then
		set_extension(".x86_64")
	end
	add_files("main.cpp")
