// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/08/2021
// Updated : 30/03/2022

#include <Audio/audioManager.h>
#include <Core/log.h>

namespace Ak
{
    AudioManager::AudioManager() : Component("__audio_manager") {}

    void AudioManager::onAttach()
    {
        _al = create_Unique_ptr<OpenAL>();
        _al->initOAL();
        _is_init = true;
    }

    audioFile AudioManager::loadSound(std::string filename)
    {
        if(!_is_init)
        {
            Core::log::report(ERROR, "Audio Manager: unable to load sound, you need to add the AudioManager component");
            return 0;
        }
        return _al->loadSound(filename);
    }

    void AudioManager::freeSound(audioFile sound)
    {
        if(!_is_init)
        {
            Core::log::report(ERROR, "Audio Manager: unable to free sound, you need to add the AudioManager component");
            return;
        }
        _al->freeSound(sound);
    }

    void AudioManager::playSound(audioFile sound)
    {
        if(!_is_init)
        {
            Core::log::report(ERROR, "Audio Manager: unable to play sound, you need to add the AudioManager component");
            return;
        }
        _al->playSound(sound);
    }

    void AudioManager::newSource()
    {
        if(!_is_init)
        {
            Core::log::report(ERROR, "Audio Manager: unable to create new source, you need to add the AudioManager component");
            return;
        }
        _al->newSource();
    }

    void AudioManager::freeSource(int index)
    {
        if(!_is_init)
        {
            Core::log::report(ERROR, "Audio Manager: unable to free source %d, you need to add the AudioManager component", index);
            return;
        }
        _al->freeSource(index);
    }

    void AudioManager::switch_to_source(int index)
    {
        if(!_is_init)
        {
            Core::log::report(ERROR, "Audio Manager: unable to switch to source %d, you need to add the AudioManager component", index);
            return;
        }
        _al->switch_to_source(index);
    }

    void AudioManager::onQuit()
    {
        _al->shutdownOAL();
        _al.reset(nullptr); // freeing _al pointer
        _is_init = false;
    }
}
