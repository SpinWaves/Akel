// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 17/05/2023

#ifndef __AK_STUDIO_DOCKS__
#define __AK_STUDIO_DOCKS__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class Docks : public Panel
{
    public:
        Docks(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~Docks() = default;
};

#endif // __AK_STUDIO_DOCKS__
