option("sandbox", { description = "Build examples", default = true })

if has_config("sandbox") then
	set_group("SandBox")
	includes("*/xmake.lua")
end
