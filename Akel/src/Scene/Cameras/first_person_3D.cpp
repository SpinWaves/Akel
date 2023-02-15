// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/05/2021
// Updated : 14/02/2023

#include <Scene/Cameras/camera3D.h>
#include <Platform/input.h>
#include <Core/core.h>

namespace Ak::Cam
{
	FirstPerson3D::FirstPerson3D() : BaseCamera(), _up(0, 1, 0), _position(0.0, 0.0, 0.0)
	{
		update_view();
	}

	FirstPerson3D::FirstPerson3D(Maths::Vec3<double> position, float fov) : BaseCamera(), _position(std::move(position)), _up(0, 1, 0), _fov(fov)
	{
		update_view();
	}

	FirstPerson3D::FirstPerson3D(double x, double y, double z, float fov) : BaseCamera(), _up(0, 1, 0), _fov(fov), _position(x, y, z)
	{
		update_view();
	}

	void FirstPerson3D::onUpdate(float aspect)
	{
		update_view();
		_target = _position + _direction;
		_view = glm::lookAt(glm::vec3(_position.X, _position.Y, _position.Z), glm::vec3(_target.X, _target.Y, _target.Z), glm::vec3(0, 1, 0))
		_proj = glm::perspective<float>(glm::radians(_fov), aspect, 0.1f, 1000.0f);
	}

	void FirstPerson3D::onEvent(Input& input)
	{
		if(_isMouseGrabed)
		{
			_theta -= input.getXRel() * _sensivity;
			_phi -= input.getYRel() * _sensivity;
		}
		if(input.getInKey(SDL_SCANCODE_ESCAPE))
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

	void FirstPerson3D::update_view()
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