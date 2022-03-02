// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/06/2021
// Updated : 03/06/2021

#ifndef __AK_ENTITY__
#define __AK_ENTITY__

#include <Akpch.h>

#include <Maths/maths.h>

enum Models
{
	CUBE,
};

namespace Ak
{
	class Entity
	{
		public:
			Entity(Models model, Maths::Vec3<double> position, Maths::Vec3<double> scale, Maths::Vec3<unsigned char> color);

		private:
			Models _model;
			Maths::Vec3<double> _position;
			Maths::Vec3<double> _scale;
			Maths::Vec3<unsigned char> _color;
	};
}

#endif // __AK_ENTITY__

