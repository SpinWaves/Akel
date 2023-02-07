// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#ifndef __AK_STUDIO_PANELS_STACK__
#define __AK_STUDIO_PANELS_STACK__

#include <AkSpch.h>

#include <Panels/Base/panel.h>

class PanelStack
{
	public:
		PanelStack() = default;

		void add_panel(Panel* panel);

		template <typename T, typename ... Args>
		inline void add_panel(Args&& ... args) { add_panel(Ak::memAlloc<T>(std::forward<Args>(args)...)); }

		void remove_panel(Panel* panel);	// Modifiers
		void remove_panel(const char* name);

		Panel* get_panel(const char* name); // Accessor
		Panel* get_panel(size_t index);

		inline std::vector<Panel*>::iterator begin() { return _panels.begin(); }
		inline std::vector<Panel*>::iterator end() { return _panels.end(); }
		inline std::vector<Panel*>::reverse_iterator rbegin() { return _panels.rbegin(); }
		inline std::vector<Panel*>::reverse_iterator rend() { return _panels.rend(); }

		inline std::vector<Panel*>::const_iterator cbegin() { return _panels.cbegin(); }
		inline std::vector<Panel*>::const_iterator cend() { return _panels.cend(); }
		inline std::vector<Panel*>::const_reverse_iterator crbegin() { return _panels.crbegin(); }
		inline std::vector<Panel*>::const_reverse_iterator crend() { return _panels.crend(); }

		~PanelStack();

		std::vector<Panel*> _panels;
};

#endif // __AK_STUDIO_PANELS_STACK__

