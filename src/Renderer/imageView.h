// This file is a part of AtlasEngine
// CREATED : 05/06/2021
// UPDATED : 06/06/2021

#ifndef __AE_VK_IMAGE_VIEW__
#define __AE_VK_IMAGE_VIEW__

#include <AEpch.h>

#include <Renderer/rendering.h>

namespace AE
{
	class ImageView : public Rendering
	{
		public:
			ImageView();
            void createImageViews();
	};
}

#endif // __AE_VK_IMAGE_VIEW__

