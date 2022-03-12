// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 11/03/2022

#include <Panels/audio_manager.h>

AudioManager::AudioManager(std::shared_ptr<Ak::ELTM> eltm) : Panel("__audio_manager")
{
    _eltm = eltm;
}

void AudioManager::onUpdate(Ak::Maths::Vec2<int>& size)
{
    if(ImGui::Begin(_eltm->getLocalText("AudioManager.name").c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
    {
        ImGui::End();
    }
}
