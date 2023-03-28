// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2023
// Updated : 28/03/2023

#ifndef __AK_AL_BUFFER__
#define __AK_AL_BUFFER__

#include <Akpch.h>

namespace Ak
{
	class AK_API AudioBuffer
	{
		public:
			AudioBuffer() = default;
			AudioBuffer(std::filesystem::path file);

			inline ALuint getBuffer() const noexcept { return _buffer; }
			void setBuffer(ALuint buffer) noexcept;

			void deleteBuffer() noexcept;

			~AudioBuffer() = default;

		private:
			void loadMP3(std::filesystem::path file);
			void loadFlac(std::filesystem::path file);
			void loadWAV(std::filesystem::path file);
			void loadOGG(std::filesystem::path file);

			ALuint _buffer = 0;
	};
}

#endif
