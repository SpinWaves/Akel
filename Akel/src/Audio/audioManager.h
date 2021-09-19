// This file is a part of Akel
// CREATED : 04/08/2021
// UPDATED : 19/09/2021

#ifndef __AK_AUDIO_MANAGER__
#define __AK_AUDIO_MANAGER__

#include <Akpch.h>
#include <Audio/openAL.h>
#include <Core/Memory/uniquePtrWrapper.h>

namespace Ak
{
    using audioFile = ALuint;

    class AudioManager
    {
        public:
            AudioManager() = delete;

            static void initAudioManager();

            static audioFile loadSound(std::string filename);
            static void playSound(audioFile sound);
            static void freeSound(audioFile sound);

            static void newSource();
            static void freeSource(int index);
            static void switch_to_source(int index);

            static void shutdownAudioManager();

            ~AudioManager() = delete;

        private:
            static inline unique_ptr_w<OpenAL> _al;
    };
}

#endif // __AK_AUDIO_MANAGER__
