// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/02/2023
// Updated : 12/03/2023

#ifndef __AK_MODEL_ATTRIBUTE__
#define __AK_MODEL_ATTRIBUTE__

#include <Akpch.h>
#include <Graphics/model.h>

namespace Ak
{
	struct AK_API ModelAttribute
	{
		Model model;

		ModelAttribute() = default;
		ModelAttribute(const Model& _model, MaterialID material = nullmaterial) : model(_model)
		{
			model.load();
			model.setMaterial(material);
		}
		ModelAttribute(Model&& _model, MaterialID material = nullmaterial) : model(_model)
		{
			model.load();
			model.setMaterial(material);
		}
		ModelAttribute(std::filesystem::path model_file, MaterialID material = nullmaterial) : model(std::move(model_file))
		{
			model.load();
			model.setMaterial(material);
		}

		~ModelAttribute()
		{
			model.destroy();
		}
	};
}

#endif
