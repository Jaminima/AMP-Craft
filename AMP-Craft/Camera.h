#ifndef __Camera
#define __Camera
#include "Vec3.h"

#define Pi 3.14159265358979323f

class Camera
{
public:
	Vec3 Position = Vec3(5.0f, 20.0f, 0.0f), Angle = Vec3(0, 0, 0);

	float cosx, cosy, cosz, sinx, siny, sinz;

	unsigned int view_width = 800, view_height = 600;

	float half_vw = view_width / 2, half_vh = view_height / 2;

	float angleToRadians(float angle) {
		return angle * Pi / 180.0f;
	}

	float fov_angle = 90, fov_radians = angleToRadians(fov_angle), fov_half_angle = fov_angle / 2;

	float fov_sin_max = sin(angleToRadians(fov_half_angle)),
		fov_cos_max = cos(angleToRadians(fov_half_angle));

	void RotateCamera(Vec3 rot)
	{
		Angle = rot + Angle + Vec3(Pi, Pi, Pi);

		Angle.x = fmodf(Angle.x, 2 * Pi) - Pi;
		Angle.y = fmodf(Angle.y, 2 * Pi) - Pi;
		Angle.z = fmodf(Angle.z, 2 * Pi) - Pi;

		cosx = cosf(Angle.x);
		cosy = cosf(Angle.y);
		cosz = cosf(Angle.z);

		sinx = sinf(Angle.x);
		siny = sinf(Angle.y);
		sinz = sinf(Angle.z);
	}

	void MoveCamera(Vec3 dir)
	{
		Position = Position + RotateDirection(dir);
	}

	Camera() { RotateCamera(Vec3(0, 0, 0)); }

	Vec3 RotateDirection(Vec3 dir) restrict(amp, cpu)
	{
		dir = Vec3(
			dir.x,
			(cosx * dir.y) + (sinx * dir.z),
			(cosx * dir.z) - (sinx * dir.y));

		dir = Vec3(
			(cosy * dir.x) + (siny * dir.z),
			dir.y,
			(cosy * dir.z) - (siny * dir.x));

		dir = Vec3(
			(cosz * dir.x) + (sinz * dir.y),
			(cosz * dir.y) - (sinz * dir.x),
			dir.z);

		return dir;
	}
};

Camera input_main_camera;

#endif