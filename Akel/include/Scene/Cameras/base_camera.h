// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 30/05/2023

#ifndef __AK_BASE_CAMERA__
#define __AK_BASE_CAMERA__

#include <Akpch.h>

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

			virtual std::string getCameraType() = 0;

			virtual ~BaseCamera() = default;

		protected:
			glm::mat4 _view = glm::mat4(1.0f);
			glm::mat4 _proj = glm::mat4(1.0f);
	};
}

#endif
