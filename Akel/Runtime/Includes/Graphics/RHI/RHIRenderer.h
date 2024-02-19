// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2024
// Updated : 19/02/2024

#ifndef __AK_RHI_RENDERER__
#define __AK_RHI_RENDERER__

#include <Graphics/PreCompiled.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIRenderer
	{
		public:
			RHIRenderer() = default;

			inline bool IsInit() const noexcept { return m_is_init; }
			virtual class RHIAPIHandle& GetAPIHandle() = 0;
			virtual class RHIDevice& GetDevice() = 0;

			virtual ~RHIRenderer() = default;

		private:
			bool m_is_init = false;
	};
}

#endif 
