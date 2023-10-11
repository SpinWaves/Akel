// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 11/10/2023

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
        std::string getSize(std::uintmax_t size);

	private:
        std::string _current_file;
        std::string _parent = Ak::VFS::getMainDirPath().string();
        std::set<std::filesystem::directory_entry> _files;
};

#endif // __AK_STUDIO_BROWSER__
