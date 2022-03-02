// This file is a part of Akel
// Author : @kbz_8
// CREATED : 04/08/2021
// UPDATED : 08/08/2021

#include <Audio/openAL.h>
#include <Core/core.h>

namespace Ak
{
    bool OpenAL::initOAL()
    {
        _device = alcOpenDevice(NULL);
        if(!_device)
        {
            Core::log::report(ERROR, "OpenAL: unable to get sound device");
            return false;
        }

        _context = alcCreateContext(_device, NULL);
        if(!_context)
        {
            Core::log::report(ERROR, "OpenAL: unable to create context");
            return false;
        }

        if(!alcMakeContextCurrent(_context))
        {
            Core::log::report(ERROR, "OpenAL: unable to make context current");
            return false;
        }

        return true;
    }

    void OpenAL::freeSound(ALuint buffer)
    {
        std::vector<ALuint*>::const_iterator it;
        it = std::find(_buffers.begin(), _buffers.end(), &buffer);
        if(it != _buffers.end())
        {
            _buffers.erase(it);
            alDeleteBuffers(1, &buffer);
        }
    }

    ALuint OpenAL::loadSound(std::string filename)
    {
        SF_INFO fileInfos;
        SNDFILE* file = sf_open(filename.c_str(), SFM_READ, &fileInfos);
        if(!file)
        {
            Core::log::report(ERROR, "SndFile: unable to open sound file " + filename);
            return 0;
        }

        ALsizei nbSamples  = static_cast<ALsizei>(fileInfos.channels * fileInfos.frames);
        ALsizei sampleRate = static_cast<ALsizei>(fileInfos.samplerate);

        std::vector<int16_t> samples(nbSamples);
        if(sf_read_short(file, &samples[0], nbSamples) < nbSamples)
        {
            Core::log::report(ERROR, "SndFile: unable to read all audio samples");
            return 0;
        }

        sf_close(file);

        ALenum format;
        switch(fileInfos.channels)
        {
            case 1: format = AL_FORMAT_MONO16;   break;
            case 2: format = AL_FORMAT_STEREO16; break;

            default: return 0;
        }

        // AL Buffer
        ALuint buffer;
        alGenBuffers(1, &buffer);

        alBufferData(buffer, format, &samples[0], nbSamples * sizeof(ALushort), sampleRate);

        if(alGetError() != AL_NO_ERROR)
        {
            Core::log::report("OpenAL: unable to generate sound Buffer for " + filename);
            return 0;
        }

        _buffers.push_back(&buffer);

        return buffer;
    }

    void OpenAL::playSound(ALuint buffer)
    {
        if(_currentSource == 0)
        {
            if(_sources.empty())
                newSource();
            _currentSource = _sources.back();
        }
        alSourcei(_currentSource, AL_BUFFER, buffer);
        alSourcePlay(_currentSource);
    }

    void OpenAL::newSource()
    {
        ALuint source;
        alGenSources(1, &source);
        _sources.push_back(source);
    }

    void OpenAL::switch_to_source(int index)
    {
        _currentSource = _sources[index];
    }

    void OpenAL::freeSource(int index)
    {
        if(_currentSource == _sources[index])
            _currentSource = 0;
        alSourcei(_sources[index], AL_BUFFER, 0);
        alDeleteSources(1, &_sources[index]);
        _sources.erase(_sources.begin() + index);
    }

    void OpenAL::shutdownOAL()
    {
        for(auto elem : _buffers)
            alDeleteBuffers(1, elem);
        _buffers.clear();

        for(auto elem : _sources)
        {
            alSourcei(elem, AL_BUFFER, 0);
            alDeleteSources(1, &elem);
        }
        _sources.clear();

        alcMakeContextCurrent(NULL);

        alcDestroyContext(_context);
        alcCloseDevice(_device);
    }
}
