// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 17/05/2023

#ifndef __AK_STUDIO_ENTITIES_MANAGER__
#define __AK_STUDIO_ENTITIES_MANAGER__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class EntitiesManager : public Panel
{
    public:
        EntitiesManager(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project, const std::vector<std::string>& materials);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~EntitiesManager() = default;

    private:
        void render_transform();
		const std::vector<std::string>& _materials;
};

#endif // __AK_STUDIO_ENTITIES_MANAGER__
