// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 05/07/2022

#include <Panels/audio_manager.h>

AudioManager::AudioManager(std::shared_ptr<Ak::ELTM> eltm) : Panel("__audio_manager")
{
    _eltm = eltm;
}

void AudioManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(_eltm->getLocalText("AudioManager.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
        if(ImGui::Button(_eltm->getLocalText("AudioManager.play").c_str()))
        {
            auto file = pfd::open_file(_eltm->getLocalText("AudioManager.load"), Ak::Core::getMainDirPath(), {"Song files (.wav)", "*.wav", "All files", "*"});	
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
