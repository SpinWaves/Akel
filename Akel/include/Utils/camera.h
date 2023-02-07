// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/05/2021
// Updated : 27/01/2023

#ifndef __AK_CAMERA__
#define __AK_CAMERA__ 

#include <Akpch.h>
#include <Maths/maths.h>
#include <Core/profile.h>
#include <Core/Components/components.h>

namespace Ak
{
	class AK_API Camera3D : public Component
	{
		public:
			Camera3D();
			Camera3D(Maths::Vec3<double> position);
			Camera3D(double x, double y, double z);

			void onAttach() override;
			void update() override;
			void onEvent(Input& input) override;

			inline void setPosition(int pos_x, int pos_y, int pos_z) noexcept { _position.SET(pos_x, pos_y, pos_z); }
			inline Maths::Vec3<double> getPosition() noexcept { return _position; }

		private:
			const float _speed = 0.3f;
			const float _sensivity = 0.7f;

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