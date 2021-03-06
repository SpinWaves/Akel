// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 09/03/2022
// Updated : 10/03/2022

#ifndef __AK_STUDIO_ENTITIES__
#define __AK_STUDIO_ENTITIES__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class Entities : public Panel
{
    public:
        Entities(std::shared_ptr<Ak::ELTM> eltm);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~Entities() = default;
};

#endif // __AK_STUDIO_ENTITIES__
