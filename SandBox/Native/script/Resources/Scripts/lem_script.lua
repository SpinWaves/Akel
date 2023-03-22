function AkelOnInit()
	print("Script init")
end

i = 1

function AkelOnUpdate(delta)
	local tranform = Ak.getAttribute("transform")
	transform.position.X = transform.position.X + i

	if transform.position.X > 10 then
		i = -1
	elseif transform.position.X < -10 then
		i = 1
	end
end

function AkelOnQuit()
	print("Script exit")
end
