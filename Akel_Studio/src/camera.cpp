// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 23/08/2022
// Updated : 22/11/2022

#include "camera.h"

SceneCamera::SceneCamera(double x, double y, double z, Ak::Maths::Vec2<int>* window_size) : Ak::Component("scene_camera"), _up(0, 1, 0)
{
	_window_size = window_size;
	_position.SET(x, y, z);
	update_view();
}

void SceneCamera::update()
{
	update_view();
	_target = _position + _direction;
	Ak::Matrixes::lookAt(_position.X, _position.Y, _position.Z, _target.X, _target.Y, _target.Z, 0, 1, 0);
}

void SceneCamera::onEvent(Ak::Input& input)
{
	if(	input.getInMouse(AK_MOUSE_BUTTON_RIGHT) && _focus &&
		input.getX() > (15 * _window_size->X)/100 - 1 && input.getX() < _window_size->X - (19 * _window_size->X)/100 &&
		input.getY() > 75 && input.getY() < _window_size->Y - _window_size->Y/4)
	{
		_is_in_action = true;
		_theta -= input.getXRel() * _sensivity;
		_phi -= input.getYRel() * _sensivity;
		SDL_WarpMouseInWindow(Ak::Render_Core::get().getWindow()->getNativeWindow(), _window_size->X / 2, _window_size->Y / 2);

		_mov.SET(0.0, 0.0, 0.0);

		if(input.getInKey(AK_KEY_W) || input.getInKey(AK_KEY_UP))  			_mov -= _forward;
		if(input.getInKey(AK_KEY_S) || input.getInKey(AK_KEY_DOWN))   		_mov += _forward;
		if(input.getInKey(AK_KEY_D) || input.getInKey(AK_KEY_RIGHT))  		_mov -= _left;
		if(input.getInKey(AK_KEY_A) || input.getInKey(AK_KEY_LEFT))   		_mov += _left;
		if(input.getInKey(AK_KEY_LSHIFT) || input.getInKey(AK_KEY_RSHIFT))	_mov -= _up;
		if(input.getInKey(AK_KEY_SPACE))									_mov += _up;

		_speed = input.getInKey(AK_KEY_Q) ? 1.5f : 0.3f;
		_position += _mov * _speed;
	}
	else
		_is_in_action = false;
}

void SceneCamera::onRender()
{
	SDL_ShowCursor(_is_in_action ? SDL_DISABLE : SDL_ENABLE);
}

void SceneCamera::update_view()
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
