// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#ifndef __AK_EDITOR_BROWSER__
#define __AK_EDITOR_BROWSER__

#include <AkEpch.h>
#include <Panels/Base/panel.h>

class Browser : public Panel
{
    public:
        Browser(std::shared_ptr<Ak::ELTM> eltm);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~Browser() = default;
};

#endif // __AK_EDITOR_BROWSER__
