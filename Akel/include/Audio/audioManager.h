// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/08/2021
// Updated : 28/03/2023

#ifndef __AK_AUDIO_MANAGER__
#define __AK_AUDIO_MANAGER__

#include <Akpch.h>
#include <Audio/openAL.h>
#include <Core/Memory/akel_unique_ptr.h>
#include <Core/Components/baseComponent.h>
#include <Core/profile.h>

namespace Ak
{
    class AK_API AudioComponent : public Component
    {
        public:
            AudioComponent();

            void onAttach() override;
            void onQuit() override;

            ~AudioComponent() = default;

        private:
            UniquePtr<OpenAL> _al;
    };
}

#endif // __AK_AUDIO_MANAGER__
