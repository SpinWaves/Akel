// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/08/2021
// Updated : 27/03/2023

#ifndef __AK_AUDIO_MANAGER__
#define __AK_AUDIO_MANAGER__

#include <Akpch.h>
#include <Audio/openAL.h>
#include <Core/Memory/uniquePtrWrapper.h>
#include <Core/Components/baseComponent.h>
#include <Core/profile.h>

namespace Ak
{
    using audioFile = ALuint;
    constexpr audioFile nullaudio = 0;

    class AK_API AudioComponent : public Component
    {
        public:
            AudioComponent();

            void onAttach() override;
            void onQuit() override;

            audioFile loadSound(std::string filename);
            void playSound(audioFile sound);
            void freeSound(audioFile sound);

            void newSource();
            void freeSource(int index);
            void switch_to_source(int index);

            ~AudioComponent() = default;

        private:
            Unique_ptr<OpenAL> _al;
    };
}

#endif // __AK_AUDIO_MANAGER__
