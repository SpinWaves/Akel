// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 23/08/2022
// Updated : 15/10/2022

#ifndef __AK_STUDIO_CAMERA__
#define __AK_STUDIO_CAMERA__

#include <AkSpch.h>

class SceneCamera : public Ak::Component
{
		public:
			SceneCamera(double x, double y, double z, Ak::Maths::Vec2<int>* window_size);

			void update() override;
			void onEvent(Ak::Input& input) override;
			inline void setFocus(bool focus) noexcept { _focus = focus; }

			~SceneCamera() = default;

		private:
			void update_view();

			Ak::Maths::Vec3<double> _position;
			Ak::Maths::Vec3<double> _left;
			Ak::Maths::Vec3<double> _forward;
			const Ak::Maths::Vec3<double> _up;
			Ak::Maths::Vec3<double> _target;
			Ak::Maths::Vec3<double> _direction;
			Ak::Maths::Vec3<double> _mov;
			Ak::Maths::Vec2<int>* _window_size = nullptr;

			double _theta = -45;
			double _phi = -20;

			float _speed = 0.3f;
			const float _sensivity = 0.9f;

			bool _focus = true;
};

#endif // __AK_STUDIO_CAMERA__

