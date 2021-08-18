// This file is a part of Akel
// CREATED : 05/05/2021
// UPDATED : 18/08/2021

#include <Utils/utils.h>
#include <Renderer/renderer.h>

namespace Ak
{
	Camera3D::Camera3D() : Component()
	{
		_position.SET(0, 0, 0);
		_phi = -79;
		_theta = 0;
		VectorsFromAngles();
		_up.SET(0, 1, 0);
		_sensivity = 0.6;
	}

	void Camera3D::setPosition(int pos_x, int pos_y, int pos_z)
	{
		_position.SET(pos_x, pos_y, pos_z);
	}

	void Camera3D::update()
	{
		_movement.SET(0, 0, 0);
		_target = _position + _direction;
	}

	void Camera3D::onEvent(Input& input)
	{
		if(_grabMouse)
		{
			_theta -= input.getXRel() * _sensivity;
			_phi -= input.getYRel() * _sensivity;
			VectorsFromAngles();
		}

		if(input.getInKey(AK_KEY_F1, UP))
		{
			_grabMouse = _grabMouse? SDL_FALSE : SDL_TRUE;
			SDL_SetRelativeMouseMode(_grabMouse);
		}
		if(!_grabMouse && input.getInMouse(1, UP))
		{
			_grabMouse = SDL_TRUE;
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}

		realspeed = (input.getInKey(AK_KEY_EXECUTE))? 10 * _speed : _speed;

		if(input.getInKey(AK_KEY_W) || input.getInKey(AK_KEY_UP))  			_movement += _forward.DirectCopy().NEGATE();
		if(input.getInKey(AK_KEY_S) || input.getInKey(AK_KEY_DOWN))   		_movement += _forward.DirectCopy();
		if(input.getInKey(AK_KEY_A) || input.getInKey(AK_KEY_LEFT))   		_movement += _left.DirectCopy();
		if(input.getInKey(AK_KEY_D) || input.getInKey(AK_KEY_RIGHT))  		_movement += _left.DirectCopy().NEGATE();
		if(input.getInKey(AK_KEY_LSHIFT) || input.getInKey(AK_KEY_RSHIFT))	_movement -= _up;
		if(input.getInKey(AK_KEY_SPACE))									_movement += _up;

		Move(_movement.X, _movement.Y, _movement.Z);     //update
	}

	void Camera3D::Move(double x, double y, double z)
	{
		_position.X += x * realspeed;
		_position.Y += y * realspeed;
		_position.Z += z * realspeed;
	}

	void Camera3D::VectorsFromAngles()
	{
		_phi = _phi > 89 ? 89 : _phi;
		_phi = _phi < -89 ? -89 : _phi;

		_direction.X = cos(_phi * M_PI / 180) * cos(_theta * M_PI / 180);
		_direction.Y = cos(_phi * M_PI / 180) * sin(_theta * M_PI / 180);	// Spherical coordinate system
		_direction.Z = sin(_phi * M_PI / 180);

		_left = _up.crossProduct(_direction);
		_left.normalize();

		_forward = _up.crossProduct(_left);
		_forward.normalize();
	}
}
