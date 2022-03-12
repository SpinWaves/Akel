// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 12/03/2022
// Updated : 12/03/2022

#ifndef __AK_STUDIO_SCENE__
#define __AK_STUDIO_SCENE__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class Scene : public Panel
{
    public:
        Scene(std::shared_ptr<Ak::ELTM> eltm);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~Scene() = default;
};

#endif // __AK_STUDIO_SCENE__
