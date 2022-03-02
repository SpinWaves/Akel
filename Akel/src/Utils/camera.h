// This file is a part of Akel
// Author : @kbz_8
// CREATED : 05/05/2021
// UPDATED : 28/06/2021

#ifndef __AK_CAMERA__
#define __AK_CAMERA__ 

#include <Akpch.h>
#include <Maths/maths.h>
#include <Core/Components/components.h>

namespace Ak
{
	class Camera3D : public Component
	{
		public:
			Camera3D();

			void onAttach() override {}
			void update() override;
			void onEvent(Input& input) override;
			void onQuit() override {}

			void setPosition(int pos_x, int pos_y, int pos_z);


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

#endif // __AK_CAMERA__
