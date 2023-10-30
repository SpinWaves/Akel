// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 30/10/2023

#ifndef __AK_STUDIO_BROWSER__
#define __AK_STUDIO_BROWSER__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class Browser : public Panel
{
    public:
        Browser(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project);
        void onUpdate(Ak::Maths::Vec2<int>& size) override;
        ~Browser() = default;

    private:
        void browser();
        void content();
		void diveInDirectory(const std::filesystem::path& path);
		void contentChild(const std::filesystem::path& path);

	private:
		std::filesystem::path _current_path;
		ImFont* _big_icons_font = nullptr;
};

#endif // __AK_STUDIO_BROWSER__
