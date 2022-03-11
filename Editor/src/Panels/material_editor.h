// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 11/03/2022

#ifndef __AK_EDITOR_MATERIAL_EDITOR__
#define __AK_EDITOR_MATERIAL_EDITOR__

#include <AkEpch.h>
#include <Panels/Base/panel.h>

class MaterialEditor : public Panel
{
    public:
        MaterialEditor(std::shared_ptr<Ak::ELTM> eltm);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~MaterialEditor() = default;
};

#endif // __AK_EDITOR_MATERIAL_EDITOR__
