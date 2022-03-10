// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#ifndef __AK_EDITOR_BASE_PANEL__
#define __AK_EDITOR_BASE_PANEL__

#include <AkEpch.h>

class Panel
{
	public:
		Panel(const char* name = "Panel");

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
		std::string _name;
		int _width, _height = 0;
		std::shared_ptr<Ak::ELTM> _eltm;
};

#endif // __AK_EDITOR_BASE_PANEL__
