// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 27/08/2022

#include <Panels/audio_manager.h>
#include <Fonts/material_font.h>

AudioManager::AudioManager(std::shared_ptr<Ak::ELTM> eltm) : Panel("__audio_manager")
{
    _eltm = std::move(eltm);
}

void AudioManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(std::string(AKS_ICON_MD_VOLUME_UP" " + _eltm->getText("AudioManager.name")).c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
        if(ImGui::Button(std::string(AKS_ICON_MD_PLAY_CIRCLE" " + _eltm->getText("AudioManager.play")).c_str()))
        {
            auto file = pfd::open_file(_eltm->getText("AudioManager.load"), Ak::Core::getMainDirPath(), {"Song files (.wav)", "*.wav", "All files", "*"});	
            if(!file.result().empty())
            {
                Ak::audioFile song = Ak::AudioManager::loadSound(file.result()[0]);
                Ak::AudioManager::playSound(song);
                Ak::AudioManager::freeSound(song);
            }
        }
        ImGui::End();
    }
}
