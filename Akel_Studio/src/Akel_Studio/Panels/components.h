// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/11/2022
// Updated : 26/05/2023

#ifndef __AK_STUDIO_COMPONENTS__
#define __AK_STUDIO_COMPONENTS__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class Components : public Panel
{
	public:
		Components(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project);

		void onUpdate(Ak::Maths::Vec2<int>& size) override;
		void onQuit() override;

		void writeComponents();

		~Components() = default;

	private:
		std::unordered_map<std::string, bool> _components;
};

#endif
