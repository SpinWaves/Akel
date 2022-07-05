// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/08/2021
// Updated : 05/07/2022

#ifndef __AK_AUDIO_MANAGER__
#define __AK_AUDIO_MANAGER__

#include <Akpch.h>
#include <Audio/openAL.h>
#include <Core/Memory/uniquePtrWrapper.h>
#include <Core/Components/baseComponent.h>

namespace Ak
{
    using audioFile = ALuint;
    constexpr audioFile null_audio = 0;

    class AudioManager : public Component
    {
        public:
            AudioManager();

            void onAttach() override;

            static audioFile loadSound(std::string filename);
            static void playSound(audioFile sound);
            static void freeSound(audioFile sound);

            static void newSource();
            static void freeSource(int index);
            static void switch_to_source(int index);

            void onQuit() override;

            ~AudioManager() = default;

        private:
            static inline Unique_ptr<OpenAL> _al;
            static inline bool _is_init = false;
    };
}

#endif // __AK_AUDIO_MANAGER__
