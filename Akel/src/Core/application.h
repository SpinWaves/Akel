// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 23/06/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>

namespace Ak
{
	class Application
	{
		public:
			Application(const std::string name);
			~Application() = default;

		private:
			std::string _name = "";
	};
}

#endif // __AK_APPLICATION__

