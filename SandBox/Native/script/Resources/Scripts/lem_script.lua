function AkelOnInit()
	print("Script init")
end

function AkelOnUpdate(delta)
	local transform = Ak.getAttribute("transform")
	transform.rotation.X = transform.rotation.X + 1
	print(transform.rotation.X)
end

function AkelOnQuit()
	print("Script exit")
end
