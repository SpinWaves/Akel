// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2023
// Updated : 27/03/2023

#ifndef __AK_AUDIO_ATTRIBUTE__
#define __AK_AUDIO_ATTRIBUTE__

#include <Akpch.h>
#include <Audio/audio.h>
#include <Core/application.h>

namespace Ak
{
	class AK_API AudioAttribute
	{
		public:
			AudioAttribute() = default;
			AudioAttribute(audioFile audio) : _audio(audio) {}
			AudioAttribute(std::filesystem::path audio)
			{
				AudioComponent* comp = static_cast<AudioComponent*>(getMainAppComponentStack()->get_component("__audio_component"));
				if(comp == nullptr)
					Core::log::report(ERROR, "Audio Attribute : you need to add Ak::AudioComponent to the application to use audio attribute");
				else
					_audio = comp->loadSound(audio.string());
			}

			inline void play()
			{
				AudioComponent* comp = static_cast<AudioComponent*>(getMainAppComponentStack()->get_component("__audio_component"));
				if(comp == nullptr)
					Core::log::report(ERROR, "Audio Attribute : you need to add Ak::AudioComponent to the application to use audio attribute");
				else
					comp->playSound(_audio);
			}

			void quit()
			{
				AudioComponent* comp = static_cast<AudioComponent*>(getMainAppComponentStack()->get_component("__audio_component"));
				if(comp == nullptr)
					Core::log::report(ERROR, "Audio Attribute : you need to add Ak::AudioComponent to the application to use audio attribute");
				else
					comp->freeSound(_audio);
			}

			~AudioAttribute() = default;

		private:
			audioFile _audio = nullaudio;
	};
}

#endif
