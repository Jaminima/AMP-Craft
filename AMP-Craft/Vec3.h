#ifndef __Vec3
#define __Vec3
#include <iostream>
#include <amp.h>
using namespace concurrency;
#include <amp_math.h>
using namespace fast_math;

class Vec3
{
public:
	float x, y, z;
	bool isNormalised = false;

	Vec3() restrict(amp, cpu) {
		x = 0;
		y = 0;
		z = 0;
	}

	Vec3(float _x, float _y, float _z) restrict(amp, cpu) {
		x = _x;
		y = _y;
		z = _z;
	}

	void ensureNormalised()restrict(amp, cpu) {
		if (!isNormalised) normalise();
	}

	void normalise()restrict(amp, cpu) {
		float vecSize = sqrtf(x * x + y * y + z * z);

		x /= vecSize;
		y /= vecSize;
		z /= vecSize;

		isNormalised = true;
	}

	Vec3 operator+(Vec3 offset)restrict(amp, cpu) {
		return Vec3(x + offset.x, y + offset.y, z + offset.z);
	}

	Vec3 operator-(Vec3 offset)restrict(amp, cpu) {
		return Vec3(x - offset.x, y - offset.y, z - offset.z);
	}

	Vec3 operator*(float mul)restrict(amp, cpu) {
		return Vec3(x * mul, y * mul, z * mul);
	}

	Vec3 operator/(Vec3 offset) restrict(amp, cpu) {
		return Vec3(x / offset.x, y / offset.y, z / offset.z);
	}

	float dotProduct(Vec3 V) restrict(amp, cpu)
	{
		return V.x * x + V.y * y + V.z * z;
	}

	Vec3 crossProduct(Vec3 V) restrict(amp, cpu)
	{
		Vec3 N(
			y * V.z - z * V.y,
			z * V.x - x * V.z,
			x * V.y - y * V.x);
		return N;
	}
};

#endif // !__Vec3
