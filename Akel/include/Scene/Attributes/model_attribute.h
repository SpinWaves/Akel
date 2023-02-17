// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/02/2023
// Updated : 17/02/2023

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
		ModelAttribute(Model& _model) : model(_model) { model.load(); }
		ModelAttribute(std::filesystem::path model_file) : model(std::move(model_file)) { model.load(); }
	};
}

#endif
