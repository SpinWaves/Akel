// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/08/2021
// Updated : 07/02/2023

#include <Audio/audioManager.h>
#include <Core/log.h>

namespace Ak
{
    AudioComponent::AudioComponent() : Component("__audio_component") {}

    void AudioComponent::onAttach()
    {
        _al = create_Unique_ptr<OpenAL>();
        _al->initOAL();
		getMainAppProjectFile().setBoolValue("__audio_component", true);
    }

    audioFile AudioComponent::loadSound(std::string filename)
    {
        return _al->loadSound(std::move(filename));
    }

    void AudioComponent::freeSound(audioFile sound)
    {
        _al->freeSound(sound);
    }

    void AudioComponent::playSound(audioFile sound)
    {
        _al->playSound(sound);
    }

    void AudioComponent::newSource()
    {
        _al->newSource();
    }

    void AudioComponent::freeSource(int index)
    {
        _al->freeSource(index);
    }

    void AudioComponent::switch_to_source(int index)
    {
        _al->switch_to_source(index);
    }

    void AudioComponent::onQuit()
    {
        _al->shutdownOAL();
        _al.reset(nullptr); // freeing _al pointer
    }
}
