// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/08/2021
// Updated : 28/03/2023

#include <Audio/audioManager.h>
#include <Core/log.h>

namespace Ak
{
	AudioComponent::AudioComponent() : Component("__audio_component") {}

	void AudioComponent::onAttach()
	{
		_al = createUniquePtr<OpenAL>();
		_al->initOAL();
	}

	void AudioComponent::onQuit()
	{
		_al->shutdownOAL();
		_al.reset(nullptr); // freeing _al pointer
	}
}
