// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 11/03/2022

#ifndef __AK_EDITOR_MATERIALS__
#define __AK_EDITOR_MATERIALS__

#include <AkEpch.h>
#include <Panels/Base/panel.h>

class Materials : public Panel
{
    public:
        Materials(std::shared_ptr<Ak::ELTM> eltm);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~Materials() = default;
};

#endif // __AK_EDITOR_MATERIALS__
