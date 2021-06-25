// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 25/06/2021

#ifndef __AK_BASE_COMPONENT__
#define __AK_BASE_COMPONENT__

#include <Akpch.h>

namespace Ak
{
	class Component
	{
		public:
			Component(const char* name = "Component");

			virtual void onAttach() {};
			virtual void update() {};
			virtual void onQuit() {};

			const char* getName();
			virtual ~Component();

		protected:
			const char* _name;
	};
}

#endif // __AK_BASE_COMPONENT__

