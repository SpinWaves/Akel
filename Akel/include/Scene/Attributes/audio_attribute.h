// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2023
// Updated : 28/03/2023

#ifndef __AK_AUDIO_ATTRIBUTE__
#define __AK_AUDIO_ATTRIBUTE__

#include <Akpch.h>
#include <Audio/audio.h>
#include <Core/application.h>

namespace Ak
{
	struct AudioAttribute
	{
		Sound sound;

		AudioAttribute() = default;
		AudioAttribute(std::filesystem::path audio) : sound(std::move(audio)) {}
		~AudioAttribute() = default;
	};
}

#endif
