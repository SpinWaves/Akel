// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 30/04/2023

#ifndef __AK_STUDIO_AUDIO_MANAGER__
#define __AK_STUDIO_AUDIO_MANAGER__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class AudioManager : public Panel
{
    public:
        AudioManager(std::shared_ptr<Ak::ELTM> eltm);
        void onUpdate(Ak::Maths::Vec2<int>& size) override;
        ~AudioManager();

	private:
		Ak::Sound _sound;
};

#endif // __AK_STUDIO_AUDIO_MANAGER__
