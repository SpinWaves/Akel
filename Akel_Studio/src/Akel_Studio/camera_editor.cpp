// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 17/08/2023
// Updated : 17/08/2023

#include <camera_editor.h>

EditorCamera3D::EditorCamera3D() : Ak::Cam::BaseCamera(), _up(0, 1, 0), _position(0.0, 0.0, 0.0)
{
	update_view();
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

EditorCamera3D::EditorCamera3D(Ak::Vec3d position, float fov) : Ak::Cam::BaseCamera(), _position(std::move(position)), _up(0, 1, 0), _fov(fov)
{
	update_view();
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

EditorCamera3D::EditorCamera3D(double x, double y, double z, float fov) : Ak::Cam::BaseCamera(), _up(0, 1, 0), _fov(fov), _position(x, y, z)
{
	update_view();
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void EditorCamera3D::onUpdate(float aspect)
{
	update_view();
	_target = _position + _direction;
	_view = glm::lookAt(glm::vec3(_position.X, _position.Y, _position.Z), glm::vec3(_target.X, _target.Y, _target.Z), glm::vec3(0, 1, 0));
	_proj = glm::perspective<float>(glm::radians(_fov), aspect, 0.1f, 1000.0f);

	if(alcGetCurrentContext() != nullptr)
	{
		alListener3f(AL_POSITION, _position.X, _position.Y, _position.Z);
		alListener3f(AL_VELOCITY, _position.X, _position.Y, _position.Z);

		ALfloat orientation[6] = { static_cast<float>(_direction.X), static_cast<float>(_direction.Y), static_cast<float>(_direction.Z), static_cast<float>(_up.X), static_cast<float>(_up.Y), static_cast<float>(_up.Z) };
		alListenerfv(AL_ORIENTATION, orientation);
	}
}

void EditorCamera3D::onEvent(Ak::Input& input)
{
	if(!_camera_in_action)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		if(!input.getInMouse(AK_MOUSE_BUTTON_LEFT) || !_is_hover)
			return;
		_camera_in_action = true;
	}
	else
	{
		if(!input.getInMouse(AK_MOUSE_BUTTON_LEFT))
		{
			_camera_in_action = false;
			return;
		}
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);

	_theta -= input.getXRel() * _sensivity;
	_phi -= input.getYRel() * _sensivity;

	_mov.set(0.0, 0.0, 0.0);

	if(input.getInKey(AK_KEY_W) || input.getInKey(AK_KEY_UP))  			_mov -= _forward;
	if(input.getInKey(AK_KEY_S) || input.getInKey(AK_KEY_DOWN))   		_mov += _forward;
	if(input.getInKey(AK_KEY_D) || input.getInKey(AK_KEY_RIGHT))  		_mov -= _left;
	if(input.getInKey(AK_KEY_A) || input.getInKey(AK_KEY_LEFT))   		_mov += _left;
	if(input.getInKey(AK_KEY_LSHIFT) || input.getInKey(AK_KEY_RSHIFT))	_mov -= _up;
	if(input.getInKey(AK_KEY_SPACE))									_mov += _up;

	_position += _mov * _speed;
}

void EditorCamera3D::update_view()
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