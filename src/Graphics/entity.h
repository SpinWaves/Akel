// This file is a part of AtlasEngine
// CREATED : 03/06/2021
// UPDATED : 03/06/2021

#ifndef __AE_ENTITY__
#define __AE_ENTITY__

#include <AEpch.h>

#include <Maths/maths.h>

enum Models
{
	CUBE,
};

namespace AE
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

#endif // __AE_ENTITY__

