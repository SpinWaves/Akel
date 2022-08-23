// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/05/2021
// Updated : 23/08/2022

#include <Utils/camera.h>
#include <Graphics/matrixes.h>
#include <Platform/input.h>

namespace Ak
{
	Camera3D::Camera3D() : Component("__camera3D"), _up(0, 1, 0)
	{
		_position.SET(0, 0, 0);
		update_view();
	}
	Camera3D::Camera3D(Maths::Vec3<double> position) :  Component("__camera3D"), _position(std::move(position)), _up(0, 1, 0)
	{
		update_view();
	}
	Camera3D::Camera3D(double x, double y, double z) : Component("__camera3D"), _up(0, 1, 0)
	{
		_position.SET(x, y, z);
		update_view();
	}

	void Camera3D::update()
	{
		update_view();
		_target = _position + _direction;
    	Matrixes::lookAt(_position.X, _position.Y, _position.Z, _target.X, _target.Y, _target.Z, 0, 1, 0);
	}

	void Camera3D::onEvent(Input& input)
	{
		if(_isMouseGrabed)
		{
			_theta -= input.getXRel() * _sensivity;
			_phi -= input.getYRel() * _sensivity;
		}
		if(input.getInKey(SDL_SCANCODE_ESCAPE, action::up))
		{
			_isMouseGrabed = false;
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		if(input.getInMouse(AK_MOUSE_BUTTON_LEFT))
		{
			_isMouseGrabed = true;
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}

		_mov.SET(0.0, 0.0, 0.0);

		if(input.getInKey(AK_KEY_W) || input.getInKey(AK_KEY_UP))  			_mov -= _forward;
		if(input.getInKey(AK_KEY_S) || input.getInKey(AK_KEY_DOWN))   		_mov += _forward;
		if(input.getInKey(AK_KEY_D) || input.getInKey(AK_KEY_RIGHT))  		_mov -= _left;
		if(input.getInKey(AK_KEY_A) || input.getInKey(AK_KEY_LEFT))   		_mov += _left;
		if(input.getInKey(AK_KEY_LSHIFT) || input.getInKey(AK_KEY_RSHIFT))	_mov -= _up;
		if(input.getInKey(AK_KEY_SPACE))									_mov += _up;

		_position += _mov * _speed;
	}

	void Camera3D::update_view()
	{
		_phi = _phi > 89 ? 89 : _phi;
		_phi = _phi < -89 ? -89 : _phi;

		_direction.X = cos(_phi * M_PI / 180) * cos(_theta * M_PI / 180);
		_direction.Y = sin(_phi * M_PI / 180);								// Spherical coordinate system
		_direction.Z = cos(_phi * M_PI / 180) * sin(-_theta * M_PI / 180);

		_left = _up.crossProduct(_direction);
		_left.normalize();

		_forward = _up.crossProduct(_left);
		_forward.normalize();
	}
}
