// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 28/06/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Core/Components/components.h>
#include <Platform/input.h>

namespace Ak
{
	class Input;

	class Application : public ComponentStack
	{
		public:
			Application(const char* name);
			void run();
			~Application() = default;

		private:
			std::string _name = "";
			Input _in;
	};
}

#endif // __AK_APPLICATION__

