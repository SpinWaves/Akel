// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 28/10/2021
// Updated : 09/07/2022

#ifndef __AK_STUDIO_ELTM_EDITOR__
#define __AK_STUDIO_ELTM_EDITOR__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class ELTM_editor : public Panel
{
    public:
        ELTM_editor(std::shared_ptr<Ak::ELTM> eltm, std::string* input_buffer, uint8_t* save);
        void onUpdate(Ak::Maths::Vec2<int>& size) override;
        void onQuit() override;
        inline void onOpen() override { _is_open = !_is_open; }
        inline bool isOpen() override { return _is_open; }
        ~ELTM_editor() = default;

    private:
        std::unordered_map<std::string, std::string> _texts;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _modules;
        
        std::string _file;
        std::string* _input_buffer = nullptr;
        Ak::Unique_ptr<Ak::ELTM> _loader;
        uint8_t* _save = nullptr;
        bool _is_open = false;

        void editor();
        static int InputCallback(ImGuiInputTextCallbackData* data);
};

#endif // __AK_STUDIO_ELTM_EDITOR__
