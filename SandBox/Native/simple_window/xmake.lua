target("SimpleWindow")
	add_deps("AkelCore")
	if is_plat("linux") then
		set_extension(".x86_64")
	end
	add_files("main.cpp")
