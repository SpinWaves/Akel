// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 27/06/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Core/Components/components.h>

namespace Ak
{
	class Application : public ComponentStack
	{
		public:
			Application(const char* name);
			void run();
			~Application() = default;

		private:
			std::string _name = "";
			bool _running = true;
	};
}

#endif // __AK_APPLICATION__

