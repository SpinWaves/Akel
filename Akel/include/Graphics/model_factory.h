// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/03/2023
// Updated : 14/10/2023

#ifndef __AK_MODEL_FACTORY__
#define __AK_MODEL_FACTORY__

#include <Akpch.h>
#include <Maths/vec2.h>
#include "model.h"

namespace Ak
{
	Model createCube();
	Model createQuad(Maths::Vec2f uv_scale = Maths::Vec2f(1.f, 1.f));
}

#endif
