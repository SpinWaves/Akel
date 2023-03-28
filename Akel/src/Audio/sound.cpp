// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2023
// Updated : 28/03/2023

#include <Audio/sound.h>

namespace Ak
{
	using namespace Maths;

	Sound::Sound(std::filesystem::path file, float gain, float pitch)
	{
		alGenSources(1, &_source);
		alSourcei(_source, AL_BUFFER, buffer->GetBuffer());

		setGain(gain);
		setPitch(pitch);
	}

	void Sound::play(bool loop)
	{
		alSourcei(_source, AL_LOOPING, loop);
		alSourcePlay(_source);
	}

	void Sound::pause()
	{
		if (!isPlaying())
			return;
		alSourcePause(_source);
	}

	void Sound::resume()
	{
		if (!isPlaying())
			return;
		alSourcePlay(_source);
	}
	
	void Sound::stop()
	{
		if (!isPlaying())
			return;
		alSourceStop(_source);
	}

	bool Sound::isPlaying() const
	{
		ALenum state;
		alGetSourcei_(source, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}

	void Sound::setGain(float gain)
	{
		_gain = gain;
		alSourcef(_source, AL_GAIN, _gain);
	}
	
	void Sound::setPitch(float pitch)
	{
		_pitch = pitch;
		alSourcef(_source, AL_PITCH, _pitch);
	}
	
	void Sound::setDirection(Maths::Vec3f direction)
	{
		_direction = direction;
		alSource3f(_source, AL_DIRECTION, _direction.X, _direction.Y, _direction.Z);
	}
	
	void Sound::setPosition(Maths::Vec3f position)
	{
		_position = position;
		alSource3f(_source, AL_POSITION, _position.X, _position.Y, _position.Z);
	}
	
	void Sound::setVelocity(Maths::Vec3f velocity)
	{
		_velocity = velocity
		alSource3f(_source, AL_VELOCITY, _velocity.X, _velocity.Y, _velocity.Z);
	}

	void Sound::destroy()
	{
		_buffer.deleteBuffer();
		alDeleteSources(1, &_source);
	}
}
