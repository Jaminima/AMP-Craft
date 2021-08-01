
#ifndef __Vec3
#define __Vec3
#include <iostream>

class Vec3
{
public:
	float x, y, z;
	bool isNormalised = false;

	Vec3(){}

	Vec3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	void ensureNormalised() {
		if (!isNormalised) normalise();
	}

	void normalise() {
		float vecSize = sqrtf(x*x + y*y + z*z);

		x /= vecSize;
		y /= vecSize;
		z /= vecSize;

		isNormalised = true;
	}

	Vec3 operator+(Vec3 offset) {
		return Vec3(x + offset.x, y + offset.y, z + offset.z);
	}

	Vec3 operator-(Vec3 offset) {
		return Vec3(x - offset.x, y - offset.y, z - offset.z);
	}

	Vec3 operator*(float mul) {
		return Vec3(x * mul, y * mul, z * mul);
	}
	
	Vec3 operator/(Vec3 offset) {
		return Vec3(x / offset.x, y / offset.y, z / offset.z);
	}
};

#endif // !__Vec3



