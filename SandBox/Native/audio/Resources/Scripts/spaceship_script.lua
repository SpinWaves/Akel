function AkelOnUpdate(delta)
	if Ak.getInKey(Ak.key.E, Ak.action.down) then
		local audio = Ak.getAttribute("audio")
		if not audio.sound:isPlaying() then
			audio.sound:play(false)
		end
	end
end
