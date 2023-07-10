function AkelOnInit()
	print("Lem script entered")
end

function AkelOnUpdate(delta)
	local transform = Ak.getAttribute("transform")
	local speed = 4
	if Ak.getInKey(Ak.key.E, Ak.action.down) then
		transform.rotation.X = transform.rotation.X + speed * delta
	end

	if Ak.getInKey(Ak.key.Q, Ak.action.down) then
		transform.rotation.X = transform.rotation.X - speed * delta
	end

	if Ak.getInKey(Ak.key.k2, Ak.action.down) then
		Ak.switchToScene("second scene")
	end
end

function AkelOnQuit()
	print("Lem script exited")
end

