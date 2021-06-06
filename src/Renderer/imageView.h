// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 06/06/2021

#ifndef __AK_VK_IMAGE_VIEW__
#define __AK_VK_IMAGE_VIEW__

#include <Akpch.h>

#include <Renderer/rendering.h>

namespace Ak
{
	class ImageView : public Rendering
	{
		public:
			ImageView();
            void createImageViews();
	};
}

#endif // __AK_VK_IMAGE_VIEW__

