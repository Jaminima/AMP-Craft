#ifndef __Ray
#define __Ray
#include "Vec3.h"

class Ray
{
public:
	Vec3 origin, direction;

	Ray() restrict(amp, cpu) {}

	Ray(Vec3 _origin, Vec3 _direction) restrict(amp, cpu) {
		origin = _origin;
		direction = _direction;
	}
};

#endif