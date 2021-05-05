// This file is a part of AtlasEngine
// CREATED : 05/05/2021
// UPDATED : 05/05/2021

#include <Utils/utils.h>
#include <Renderer/renderer.h>

namespace AE
{
	Camera::Camera(int pos_x, int pos_y, int pos_z)
	{
		_position.SET(pos_x, pos_y, pos_z);
		_phi = -79;
		_theta = 0;
		VectorsFromAngles();
		_up.SET(0, 1, 0);
		_sensivity = 0.6;
	}

	void Camera::setPosition(int pos_x, int pos_y, int pos_z)
	{
		_position.SET(pos_x, pos_y, pos_z);
	}

	void Camera::OnMouseMotion(Input &input)
	{
		_theta -= input.getXRel() * _sensivity;
		_phi -= input.getYRel() * _sensivity;
		VectorsFromAngles();
	}


	void Camera::update(Input &input)
	{
		_movement.SET(0, 0, 0);

		realspeed = (input.getInKey(AE_KEY_EXECUTE))? 10 * _speed : _speed;

		if(input.getInKey(AE_KEY_W) || input.getInKey(AE_KEY_UP))  			_movement += _forward.DirectCopy().NEGATE();
		if(input.getInKey(AE_KEY_S) || input.getInKey(AE_KEY_DOWN))   		_movement += _forward.DirectCopy();
		if(input.getInKey(AE_KEY_A) || input.getInKey(AE_KEY_LEFT))   		_movement += _left.DirectCopy();
		if(input.getInKey(AE_KEY_D) || input.getInKey(AE_KEY_RIGHT))  		_movement += _left.DirectCopy().NEGATE();
		if(input.getInKey(AE_KEY_LSHIFT) || input.getInKey(AE_KEY_RSHIFT))	_movement -= _up;
		if(input.getInKey(AE_KEY_SPACE))										_movement += _up;

		Move(_movement.X, _movement.Y, _movement.Z);     //update
	}


	void Camera::Move(double x, double y, double z)
	{
		_position.X += x * realspeed;
		_position.Y += y * realspeed;
		_position.Z += z * realspeed;
	}

	void Camera::VectorsFromAngles()
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

	void Camera::look()
	{
		_target = _position + _direction;

		GL::Matrixes::MatrixMode(AE_VIEW_MATRIX);
		GL::Matrixes::LoadIdentity();
		GL::Matrixes::lookAt(_position.X, _position.Y, _position.Z, _target.X, _target.Y, _target.Z, 0, 1, 0);
	}
}

