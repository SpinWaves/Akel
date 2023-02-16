// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/05/2021
// Updated : 16/02/2023

#ifndef __AK_FIRST_PERSON_CAMERA_3D__
#define __AK_FIRST_PERSON_CAMERA_3D__ 

#include <Akpch.h>
#include <Maths/maths.h>
#include <Scene/Cameras/base_camera.h>
#include <Platform/input.h>

namespace Ak::Cam
{
	class AK_API FirstPerson3D : public BaseCamera
	{
		public:
			FirstPerson3D();
			FirstPerson3D(Maths::Vec3<double> position, float fov = 90.0f);
			FirstPerson3D(double x, double y, double z, float fov = 90.0f);

			void onUpdate(float aspect) override;
			void onEvent(Input& input) override;

			~FirstPerson3D() = default;

		private:
			void update_view();

			const Maths::Vec3<double> _up;
			Maths::Vec3<double> _position;
			Maths::Vec3<double> _left;
			Maths::Vec3<double> _forward;
			Maths::Vec3<double> _target;
			Maths::Vec3<double> _direction;
			Maths::Vec3<double> _mov;

			double _theta = 0.0;
			double _phi = 0.0;

			const float _speed = 0.3f;
			const float _sensivity = 0.7f;
			float _fov = 90.0f;

			bool _isMouseGrabed = false;
	};
}

#endif // __AK_FIRST_PERSON_CAMERA_3D__
