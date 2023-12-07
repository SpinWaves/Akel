// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 17/08/2023
// Updated : 22/11/2023

#ifndef __AK_STUDIO_EDITOR_CAMERA_3D__
#define __AK_STUDIO_EDITOR_CAMERA_3D__ 

#include <AkSpch.h>

class EditorCamera3D : public Ak::Cam::BaseCamera
{
	public:
		EditorCamera3D();
		EditorCamera3D(Ak::Vec3d position, float fov = 90.0f);
		EditorCamera3D(double x, double y, double z, float fov = 90.0f);

		void onUpdate(float aspect) override;
		void onEvent(Ak::Input& input) override;

		inline std::string getCameraType() override { return "EditorCamera3D"; }
		inline static void setHover(bool hover) noexcept { _is_hover = hover; }
		inline void setSensitivity(float sensitivity) noexcept { _sensivity = sensitivity; }

		~EditorCamera3D() = default;

	private:
		void update_view();

		const Ak::Vec3d _up;
		Ak::Vec3d _position;
		Ak::Vec3d _left;
		Ak::Vec3d _forward;
		Ak::Vec3d _target;
		Ak::Vec3d _direction;
		Ak::Vec3d _mov;

		double _theta = 0.0;
		double _phi = 0.0;

		const float _speed = 0.3f;
		float _sensivity = 0.7f;
		float _fov = 90.0f;

		inline static bool _is_hover = false;
		bool _camera_in_action = false;
};

#endif
