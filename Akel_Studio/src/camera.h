// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 23/08/2022
// Updated : 23/08/2022

#ifndef __AK_STUDIO_CAMERA__
#define __AK_STUDIO_CAMERA__

#include <AkSpch.h>

class SceneCamera : public Ak::Component
{
		public:
			SceneCamera(double x, double y, double z, Ak::Maths::Vec2<int>* window_size);

			void update() override;
			void onEvent(Ak::Input& input) override;

			~SceneCamera() = default;

		private:
			float _speed = 0.3f;
			const float _sensivity = 0.9f;

			void update_view();

			double _theta = -45;
			double _phi = -20;

			bool _isMouseGrabed = false;
			Ak::Maths::Vec2<int>* _window_size = nullptr;
			Ak::Maths::Vec3<double> _position;
			Ak::Maths::Vec3<double> _left;
			Ak::Maths::Vec3<double> _forward;
			const Ak::Maths::Vec3<double> _up;
			Ak::Maths::Vec3<double> _target;
			Ak::Maths::Vec3<double> _direction;
			Ak::Maths::Vec3<double> _mov;
};

#endif // __AK_STUDIO_CAMERA__

