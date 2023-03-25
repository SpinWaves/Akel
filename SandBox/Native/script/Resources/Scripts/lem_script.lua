function AkelOnInit()
	print("Script init")
end

function AkelOnUpdate(delta)
	local transform = Ak.getAttribute("transform")
	if Ak.getInKey(Ak.key.E, Ak.action.down) then
		transform.rotation.X = transform.rotation.X + 0.05
	end
	if Ak.getInKey(Ak.key.Q, Ak.action.down) then
		transform.rotation.X = transform.rotation.X - 0.05
	end
end

function AkelOnQuit()
	print("Script exit")
end
