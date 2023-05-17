// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 17/05/2023

#ifndef __AK_STUDIO_BASE_PANEL__
#define __AK_STUDIO_BASE_PANEL__

#include <AkSpch.h>

class Panel
{
	public:
		Panel(const char* name, Ak::Core::ProjectFile& project);

		virtual void onAttach();
		virtual void onOpen();
		virtual bool isOpen();
		virtual void onUpdate(Ak::Maths::Vec2<int>& size);
		virtual void onEvent(Ak::Input& input);
		virtual void onQuit();

		inline const char* getName() noexcept { return _name.c_str(); }
		inline void setName(const char* name) noexcept { _name = name; }
		virtual ~Panel();

	protected:
		Ak::Core::ProjectFile& _project;
		std::string _name;
		std::shared_ptr<Ak::ELTM> _eltm;
		int _width, _height = 0;
};

#endif // __AK_STUDIO_BASE_PANEL__
