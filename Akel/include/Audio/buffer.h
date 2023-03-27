// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2023
// Updated : 27/03/2023

#ifndef __AK_AL_BUFFER__
#define __AK_AL_BUFFER__

#include <Akpch.h>

namespace Ak
{
	class AK_API AudioBuffer
	{
		public:
			AudioBuffer() = default;

			inline ALuint getBuffer() const noexcept { return _buffer; }
			inline void setBuffer(ALuint buffer) noexcept { _buffer = buffer; }

			~AudioBuffer() = default;

		private:
			ALuint _buffer = 0;
	};
}

#endif
