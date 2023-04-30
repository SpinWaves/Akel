// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2023
// Updated : 30/04/2023

#include <Audio/sound.h>
#include <Audio/openAL.h>

namespace Ak
{
	using namespace Maths;

	Sound::Sound(std::filesystem::path file, float gain, float pitch) :
		_buffer(std::move(file)), _position(0.0f, 0.0f, 0.0f),
		_direction(0.0f, 0.0f, 0.0f), _velocity(0.0f, 0.0f, 0.0f)
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		alGenSources(1, &_source);
		alSourcei(_source, AL_BUFFER, _buffer.getBuffer());
		alSourcei(_source, AL_SOURCE_RELATIVE, AL_TRUE);
		checkAl(alGetError());

		setGain(gain);
		setPitch(pitch);

		setPosition(_position);
		setDirection(_direction);
		setVelocity(_velocity);
	}

	void Sound::reload(std::filesystem::path file, float gain, float pitch)
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		_buffer.deleteBuffer();
		_buffer = AudioBuffer(std::move(file));
		if(_source == 0)
		{
			alGenSources(1, &_source);
			alSourcei(_source, AL_BUFFER, _buffer.getBuffer());
			alSourcei(_source, AL_SOURCE_RELATIVE, AL_TRUE);
			checkAl(alGetError());
		}
		setGain(gain);
		setPitch(pitch);
	}

	void Sound::play(bool loop)
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		alSourcei(_source, AL_LOOPING, loop);
		alSourcePlay(_source);
		checkAl(alGetError());
	}

	void Sound::pause()
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		if (!isPlaying())
			return;
		alSourcePause(_source);
		checkAl(alGetError());
	}

	void Sound::resume()
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		if (!isPlaying())
			return;
		alSourcePlay(_source);
		checkAl(alGetError());
	}
	
	void Sound::stop()
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		if (!isPlaying())
			return;
		alSourceStop(_source);
		checkAl(alGetError());
	}

	bool Sound::isPlaying() const
	{
		if(alcGetCurrentContext() == nullptr)
			return false;
		ALenum state;
		alGetSourcei(_source, AL_SOURCE_STATE, &state);
		checkAl(alGetError());
		return state == AL_PLAYING;
	}

	void Sound::setGain(float gain) noexcept
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		_gain = gain;
		alSourcef(_source, AL_GAIN, _gain);
		checkAl(alGetError());
	}
	
	void Sound::setPitch(float pitch) noexcept
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		_pitch = pitch;
		alSourcef(_source, AL_PITCH, _pitch);
		checkAl(alGetError());
	}
	
	void Sound::setDirection(Maths::Vec3f direction) noexcept
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		_direction = direction;
		alSource3f(_source, AL_DIRECTION, _direction.X, _direction.Y, _direction.Z);
		checkAl(alGetError());
	}
	
	void Sound::setPosition(Maths::Vec3f position) noexcept
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		_position = position;
		alSource3f(_source, AL_POSITION, _position.X, _position.Y, _position.Z);
		checkAl(alGetError());
	}
	
	void Sound::setVelocity(Maths::Vec3f velocity) noexcept
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		_velocity = velocity;
		alSource3f(_source, AL_VELOCITY, _velocity.X, _velocity.Y, _velocity.Z);
		checkAl(alGetError());
	}

	void Sound::destroy() noexcept
	{
		if(alcGetCurrentContext() == nullptr)
			return;
		_buffer.deleteBuffer();
		alDeleteSources(1, &_source);
		_source = 0;
		checkAl(alGetError());
	}
}
