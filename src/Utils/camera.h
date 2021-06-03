// This file is a part of AtlasEngine
// CREATED : 05/05/2021
// UPDATED : 03/06/2021

#ifndef __AE_CAMERA__
#define __AE_CAMERA__ 

#include <AEpch.h>
#include <Platform/platform.h>
#include <Maths/maths.h>

namespace AE
{
	class Input;
	class Window;

	class Camera3D
	{
		public:
			Camera3D(int pos_x, int pos_y, int pos_z);

			void update(Input &input);
			void update(Window &win);
			void setPosition(int pos_x, int pos_y, int pos_z);

			void look();

		private:
			double _speed;
			double _sensivity;

			double _theta;
			double _phi;

			double realspeed;
			
			SDL_bool _grabMouse = SDL_FALSE;

			void VectorsFromAngles();
			void Move(double x, double y, double z);

			Maths::Vec3<double> _movement;

			Maths::Vec3<double> _position;
			Maths::Vec3<double> _left;
			Maths::Vec3<double> _forward;
			Maths::Vec3<double> _up;
			Maths::Vec3<double> _target;
			Maths::Vec3<double> _direction;
	};
}

#endif // __AE_CAMERA__
