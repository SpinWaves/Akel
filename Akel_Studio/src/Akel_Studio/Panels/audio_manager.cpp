// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 07/06/2023

#include <Panels/audio_manager.h>
#include <Fonts/material_font.h>

AudioManager::AudioManager(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__audio_manager", project)
{
	_eltm = std::move(eltm);
}

void AudioManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
	if(ImGui::Begin(std::string(AKS_ICON_MD_VOLUME_UP" " + _eltm->getText("AudioManager.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		if(ImGui::Button(std::string(AKS_ICON_MD_PLAY_CIRCLE" " + _eltm->getText("AudioManager.play")).c_str()))
		{
			auto file = pfd::open_file(_eltm->getText("AudioManager.load"), Ak::VFS::getMainDirPath(), {"Song files (.wav)", "*.wav", "All files", "*"});	
			if(!file.result().empty())
			{
				if(_sound.isPlaying())
					_sound.stop();
				_sound.reload(file.result()[0]);
				_sound.play();
			}
		}
		ImGui::End();
	}
}

AudioManager::~AudioManager()
{
	_sound.destroy();
}
