// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/05/2023
// Updated : 05/06/2023

#include <Scene/scene.h>
#include <Scene/scene_serializer.h>
#include <Scene/Cameras/base_camera.h>
#include <Scene/Attributes/attributes.h>
#include <Scene/Cameras/first_person_3D.h>

namespace Ak
{
	SceneSerializer::SceneSerializer(Scene* scene) : _scene(scene) {}

	void SceneSerializer::serialize(std::filesystem::path file)
	{
		json j;
		j["camera"] = _scene->_camera->getCameraType();
		std::size_t count = 0;
		_scene->getRegistry().each([&](entt::entity entityID)
		{
			Entity entity(entityID, _scene);

			std::string id = std::string("entity_") + std::to_string(count);
			j[id] = json::object();

			if(entity.hasAttribute<NameAttribute>())
				j[id]["nameAttribute"] = entity.getAttribute<NameAttribute>().name;

			if(entity.hasAttribute<TransformAttribute>())
			{
				TransformAttribute& trans = entity.getAttribute<TransformAttribute>();
				std::array<float, 3> pos = { trans.position.X, trans.position.Y, trans.position.Z };
				std::array<float, 3> rot = { trans.rotation.X, trans.rotation.Y, trans.rotation.Z };
				std::array<float, 3> sca = { trans.scale.X, trans.scale.Y, trans.scale.Z };
				j[id]["transformAttribute"]["position"] = pos;
				j[id]["transformAttribute"]["rotation"] = rot;
				j[id]["transformAttribute"]["scale"] = sca;
			}

			if(entity.hasAttribute<ModelAttribute>())
			{
				j[id]["modelAttribute"]["file"] = entity.getAttribute<ModelAttribute>().model.getFile().string();
			}
			count++;
		});
		writeJson(j, file);
	}

	void SceneSerializer::deserialize(std::filesystem::path file)
	{
		json j;
		if(!loadJson(file, j))
			Core::log::report(ERROR, "Scene Serializer : unable to deserialize from file '%s'", file.string().c_str());
		for(auto& [key, val] : j.items())
		{
			if(key == "camera")
			{
				if(val == "firstPerson3D")
					_scene->addCamera<Cam::FirstPerson3D>(0.0f, 0.0f, 0.0f);
				else
					Core::log::report(ERROR, "Scene Deserializer : unkown camera");
			}
			if(key.compare(0, 7, "entity_") != 0)
				continue;
			Entity entity = val.contains("nameAttribute") ? _scene->createEntity(val["nameAttribute"]) : _scene->createEntity();

			if(val.contains("transformAttribute"))
			{
				std::array<float, 3> pos;
				std::array<float, 3> rot;
				std::array<float, 3> sca;
				for(int i = 0; i < 3; i++)
				{
					pos[i] = val["transformAttribute"]["position"][i];
					rot[i] = val["transformAttribute"]["rotation"][i];
					sca[i] = val["transformAttribute"]["scale"][i];
				}
				auto& trans = entity.addAttribute<TransformAttribute>();
				trans.position.set(pos[0], pos[1], pos[2]);
				trans.rotation.set(rot[0], rot[1], rot[2]);
				trans.scale.set(sca[0], sca[1], sca[2]);
			}

			if(val.contains("modelAttribute"))
			{
				entity.addAttribute<ModelAttribute>(VFS::resolve(val["modelAttribute"]["file"]));
			}
		}
	}
}
