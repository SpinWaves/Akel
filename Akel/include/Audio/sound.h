// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2023
// Updated : 30/04/2023

#ifndef __AK_SOUND__
#define __AK_SOUND__

#include <Akpch.h>
#include <Audio/buffer.h>
#include <Maths/vec3.h>

namespace Ak
{
	class AK_API Sound
	{
		public:
			Sound() = default;
			Sound(std::filesystem::path file, float gain = 1.0f, float pitch = 1.0f);

			void reload(std::filesystem::path file, float gain = 1.0f, float pitch = 1.0f);

			void play(bool loop = false);
			void pause();
			void resume();
			void stop();

			bool isPlaying() const;

			inline float getGain() const noexcept { return _gain; }
			inline float getPitch() const noexcept { return _pitch; }

			void setGain(float gain) noexcept;
			void setPitch(float pitch) noexcept;
			void setDirection(Maths::Vec3f direction) noexcept;
			void setPosition(Maths::Vec3f position) noexcept;
			void setVelocity(Maths::Vec3f velocity) noexcept;

			void destroy() noexcept;

			~Sound() = default;

		private:
			Maths::Vec3f _position;
			Maths::Vec3f _direction;
			Maths::Vec3f _velocity;

			float _gain = 1.0f;
			float _pitch = 1.0f;

			AudioBuffer _buffer;
			ALuint _source = 0;
	};
}

#endif
