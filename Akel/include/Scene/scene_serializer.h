// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/05/2023
// Updated : 04/06/2023

#ifndef __AK_SCENE_SERIALIZER__
#define __AK_SCENE_SERIALIZER__

#include <Akpch.h>

namespace Ak
{
	using json = nlohmann::json;

	class AK_API SceneSerializer
	{
		public:
			SceneSerializer(class Scene* scene);
			void serialize(const std::filesystem::path& file);
			void deserialize(const std::filesystem::path& file);
			~SceneSerializer() = default;

		private:
			class Scene* _scene = nullptr;
	};
}

#endif
