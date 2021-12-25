// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 25/12/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Platform/input.h>
#include <Core/Components/components.h>
#include <Utils/fps.h>

namespace Ak
{
	class Application : public ComponentStack
	{
		public:
			Application(const char* name = "application");
			void run();
			void end();
			~Application();

		private:
			const char* _name = "";
			Input _in;
			CounterFPS _fps;
	};
}

#endif // __AK_APPLICATION__
