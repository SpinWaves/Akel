// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#ifndef __AK_VK_GRAPHIC_PIPELINE__
#define __AK_VK_GRAPHIC_PIPELINE__

#include "pipeline.h"

namespace Ak
{
	class GraphicPipeline : public Pipeline
	{
		public:
			GraphicPipeline();

			Shader& getShader() override { return _shader; }

		private:
			Shader _shader;
	};
}

#endif // __AK_VK_GRAPHIC_PIPELINE__
