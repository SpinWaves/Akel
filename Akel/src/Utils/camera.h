// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/05/2021
// Updated : 06/03/2022

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

			void update() override;
			void onEvent(Input& input) override;

			inline void setPosition(int pos_x, int pos_y, int pos_z) noexcept { _position.SET(pos_x, pos_y, pos_z); }
			inline Maths::Vec3<double> getPosition() noexcept { return _position; }

		private:
			float _speed = 0.15f;
			const float _sensivity = 0.8f;

			void update_view();

			double _theta = 0;
			double _phi = -79;

			bool _isMouseGrabed = false;

			Maths::Vec3<double> _position;
			Maths::Vec3<double> _left;
			Maths::Vec3<double> _forward;
			const Maths::Vec3<double> _up;
			Maths::Vec3<double> _target;
			Maths::Vec3<double> _direction;
			Maths::Vec3<double> _mov;
	};
}

#endif // __AK_CAMERA__
