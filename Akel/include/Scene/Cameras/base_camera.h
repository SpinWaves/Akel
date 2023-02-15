// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 14/02/2023

#ifndef __AK_BASE_CAMERA__
#define __AK_BASE_CAMERA__

#include <Core/profile.h>

namespace Ak::Cam
{
	class AK_API BaseCamera
	{
		public:
			BaseCamera() = default;

			virtual void onUpdate(float aspect) {};
			virtual void onEvent(class Input& input) {};

			inline const glm::mat4& getView() const noexcept { return _view; }
			inline const glm::mat4& getProj() const noexcept { return _proj; }

			virtual ~BaseCamera() = default;

		private:
			glm::mat4 _view(1.0f);
			glm::mat4 _proj(1.0f);
	};
}

#endif