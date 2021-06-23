// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 23/06/2021

#ifndef __AK_BASE_COMPONENT__
#define __AK_BASE_COMPONENT__

namespace Ak
{
	class BaseComponent
	{
		public:
			BaseComponent(const char* name = "Component");
			virtual void update() {};
			virtual ~BaseComponent();

		protected:
			const char* _name;
	};
}

#endif // __AK_BASE_COMPONENT__

