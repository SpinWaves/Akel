// This file is a part of Akel
// CREATED : 04/08/2021
// UPDATED : 04/08/2021

#include <Audio/audioManager.h>
#include <Core/core.h>

namespace Ak
{
    void AudioManager::initAudioManager()
    {
    #ifdef AK_USE_MEMORY_HELPER
        _al = shared_ptr_w<OpenAL>(custom_malloc<OpenAL>());
    #else
        _al = std::shared_ptr<OpenAL>(new OpenAl);
    #endif
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
    }
}
