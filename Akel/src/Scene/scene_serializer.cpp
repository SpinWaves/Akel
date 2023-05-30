// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/05/2023
// Updated : 30/05/2023

#include <Scene/scene.h>
#include <Scene/scene_serializer.h>
#include <Scene/Cameras/base_camera.h>
#include <Scene/Attributes/attributes.h>
#include <Scene/Cameras/first_person_3D.h>

namespace Ak
{
	SceneSerializer::SceneSerializer(Scene* scene) : _scene(scene) {}

	void SceneSerializer::serialize(const std::filesystem::path& file)
	{
		std::size_t count = 0;
		_json["camera"] = _scene->_camera->getCameraType();
		_scene->getRegistry().each([&](auto entityID)
		{
			Entity entity(entityID, _scene);

			std::string id = std::string("entity_") + std::to_string(count);
			_json[id] = json::object();

			if(entity.hasAttribute<NameAttribute>())
				_json[id]["nameAttribute"] = entity.getAttribute<NameAttribute>().name;

			if(entity.hasAttribute<TransformAttribute>())
			{
				TransformAttribute& trans = entity.getAttribute<TransformAttribute>();
				std::array<float, 3> pos = { trans.position.X, trans.position.Y, trans.position.Z };
				std::array<float, 3> rot = { trans.rotation.X, trans.rotation.Y, trans.rotation.Z };
				std::array<float, 3> sca = { trans.scale.X, trans.scale.Y, trans.scale.Z };
				_json[id]["transformAttribute"]["position"] = pos;
				_json[id]["transformAttribute"]["rotation"] = rot;
				_json[id]["transformAttribute"]["scale"] = sca;
			}

			if(entity.hasAttribute<ModelAttribute>())
			{
				_json[id]["modelAttribute"]["file"] = entity.getAttribute<ModelAttribute>().model.getFile().string();
			}

			count++;
		});
		writeJson(_json, file);
	}

	void SceneSerializer::deserialize(const std::filesystem::path& file)
	{
		if(!loadJson(file, _json))
			Core::log::report(ERROR, "Scene Serializer : unable to deserialize from file '%s'", file.string().c_str());
		for(auto& [key, val] : _json.items())
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
					pos[i] = val["modelAttribute"]["position"][i];
					rot[i] = val["modelAttribute"]["rotation"][i];
					sca[i] = val["modelAttribute"]["scale"][i];
				}
				auto& trans = entity.addAttribute<TransformAttribute>();
				trans.position.set(pos[0], pos[1], pos[2]);
				trans.rotation.set(rot[0], rot[1], rot[2]);
				trans.scale.set(sca[0], sca[1], sca[2]);
			}

			if(val.contains("modelAttribute"))
			{
				entity.addAttribute<ModelAttribute>(val["modelAttribute"]["file"]);
			}
		}
	}
}
