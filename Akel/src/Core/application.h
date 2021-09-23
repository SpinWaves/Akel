// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 23/09/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Core/Components/components.h>

namespace Ak
{
	class Application : public ComponentStack
	{
		public:
			Application(const char* name = "application");
			void run();
			~Application();

		private:
			const char* _name = "";
	};
}

#endif // __AK_APPLICATION__
