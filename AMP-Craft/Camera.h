#ifndef __Camera
#define __Camera
#include "Vec3.h"

const float Pi = 3.14f, Pi2 = Pi * 2;

class Camera
{
public:
	Vec3 Position = Vec3(5.0f,5.0f,0.0f), Angle;

	float cosx, cosy, cosz, sinx, siny, sinz;

	void RotateCamera(Vec3 rot)
	{
		Angle = rot + Angle + Vec3(Pi, Pi, Pi);

		Angle.x = fmodf(Angle.x, Pi2) - Pi;
		Angle.y = fmodf(Angle.y, Pi2) - Pi;
		Angle.z = fmodf(Angle.z, Pi2) - Pi;

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

	Vec3 RotateDirection(Vec3 dir)
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

#endif