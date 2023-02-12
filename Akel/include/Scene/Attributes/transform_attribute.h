// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 12/02/2023

#ifndef __AK_TRANSFORM_ATTRIBUTE__
#define __AK_TRANSFORM_ATTRIBUTE__

#include <Akpch.h>
#include <Maths/vec3.h>

namespace Ak
{
	class AK_API TransformAttribute
	{
		Vec3f translation = { 0.0f, 0.0f, 0.0f };
		Vec3f rotation = { 0.0f, 0.0f, 0.0f };
		Vec3f scale = { 1.0f, 1.0f, 1.0f };

		TransformAttribute() = default;
		TransformAttribute(Vec3f trans) : translation(std::move(trans)) {}

		inline glm::mat4 getTransform() const
		{
			glm::mat4 rot = glm::toMat4(glm::quat(rotation));
			return glm::translate(glm::mat4(1.0f), translation) * rot * glm::scale(glm::mat4(1.0f), scale);
		}
	};
}

#endif