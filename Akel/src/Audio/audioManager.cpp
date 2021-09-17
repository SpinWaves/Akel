// This file is a part of Akel
// CREATED : 04/08/2021
// UPDATED : 17/09/2021

#include <Audio/audioManager.h>

namespace Ak
{
    void AudioManager::initAudioManager()
    {
        _al = custom_malloc<OpenAL>();
        _al->initOAL();
    }

    audioFile AudioManager::loadSound(std::string filename)
    {
        return _al->loadSound(filename);
    }

    void AudioManager::freeSound(audioFile sound)
    {
        _al->freeSound(sound);
    }

    void AudioManager::playSound(audioFile sound)
    {
        _al->playSound(sound);
    }

    void AudioManager::newSource()
    {
        _al->newSource();
    }

    void AudioManager::freeSource(int index)
    {
        _al->freeSource(index);
    }

    void AudioManager::switch_to_source(int index)
    {
        _al->switch_to_source(index);
    }

    void AudioManager::shutdownAudioManager()
    {
        _al->shutdownOAL();
        custom_free(_al);
    }
}
