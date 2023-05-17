// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 11/03/2022
// Updated : 17/05/2023

#ifndef __AK_STUDIO_MATERIALS__
#define __AK_STUDIO_MATERIALS__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class Materials : public Panel
{
    public:
        Materials(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;
		inline const std::vector<std::string>& getNames() const { return _names; }

        ~Materials() = default;

	private:
		std::vector<std::string> _names;
		bool _new_material;
};

#endif // __AK_STUDIO_MATERIALS__
