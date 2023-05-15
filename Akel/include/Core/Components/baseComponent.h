// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 15/05/2023

#ifndef __AK_BASE_COMPONENT__
#define __AK_BASE_COMPONENT__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
	class AK_API Component
	{
		public:
			Component() = delete;
			Component(std::string name);

			virtual void onAttach();
			virtual void update();
			virtual void onRender();
			virtual void onImGuiRender();
			virtual void onImGuiEvent(class Input& input);
			virtual void onEvent(class Input& input);
			virtual void onQuit();

			inline const std::string& getName() const { return _name; }
			virtual ~Component();

		protected:
			std::string _name;
	};
}

#endif // __AK_BASE_COMPONENT__
