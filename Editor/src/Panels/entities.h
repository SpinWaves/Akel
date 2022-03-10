// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 09/03/2022
// Updated : 10/03/2022

#ifndef __AK_EDITOR_ENTITIES__
#define __AK_EDITOR_ENTITIES__

#include <AkEpch.h>
#include <Panels/Base/panel.h>

class Entities : public Panel
{
    public:
        Entities(std::shared_ptr<Ak::ELTM> eltm);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~Entities() = default;
};

#endif // __AK_EDITOR_ENTITIES__
