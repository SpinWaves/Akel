// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 16/02/2023

#ifndef __AK_TRANSFORM_ATTRIBUTE__
#define __AK_TRANSFORM_ATTRIBUTE__

#include <Akpch.h>
#include <Maths/vec3.h>

namespace Ak
{
	struct AK_API TransformAttribute
	{
		Maths::Vec3f translation = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3f rotation = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3f scale = { 1.0f, 1.0f, 1.0f };

		TransformAttribute() = default;
		TransformAttribute(Maths::Vec3f trans) : translation(std::move(trans)) {}

		inline glm::mat4 getTransform() const
		{
			glm::vec3 glm_rot(rotation.X, rotation.Y, rotation.Z);
			glm::vec3 glm_trans(translation.X, translation.Y, translation.Z);
			glm::vec3 glm_scale(scale.X, scale.Y, scale.Z);
			glm::mat4 rot = glm::toMat4(glm::quat(glm_rot));
			return glm::translate(glm::mat4(1.0f), glm_trans) * rot * glm::scale(glm::mat4(1.0f), glm_scale);
		}
	};
}

#endif
