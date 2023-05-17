// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 17/05/2023

#ifndef __AK_STUDIO_MATERIAL_EDITOR__
#define __AK_STUDIO_MATERIAL_EDITOR__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class MaterialEditor : public Panel
{
    public:
        MaterialEditor(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project, const std::vector<std::string>& names);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~MaterialEditor() = default;

	private:
		const std::vector<std::string>& _names;
};

#endif // __AK_STUDIO_MATERIAL_EDITOR__
