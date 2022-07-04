// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 28/10/2021
// Updated : 04/07/2022

#ifndef __AK_STUDIO_ELTM_EDITOR__
#define __AK_STUDIO_ELTM_EDITOR__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class ELTM_editor : public Panel
{
    public:
        ELTM_editor(const std::string& name, std::string* input_buffer);
        void onUpdate(Ak::Maths::Vec2<int>& size) override;
        inline void onOpen() override { _is_open = _is_open ? false : true; }
        inline bool isOpen() override { return _is_open; }
        ~ELTM_editor() = default;
    
    private:
        std::string _file;
        std::string _name;
        bool _is_open = false;

        std::string* _input_buffer = nullptr;

        void editor();
};

#endif // __AK_STUDIO_ELTM_EDITOR__
