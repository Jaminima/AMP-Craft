#ifndef __SteppedRay
#define __SteppedRay
#include "Ray.h"

class SteppedRay :
	public Ray
{
public:
	float direction_mul = 1.0f;
	unsigned int steps = 0;

	SteppedRay() restrict(amp, cpu) : Ray(Vec3(), Vec3()) {}

	SteppedRay(Vec3 _origin, Vec3 _direction) restrict(amp, cpu) : Ray(_origin, _direction) {
		_direction.ensureNormalised();
	}

	Vec3 GetPoint() restrict(amp, cpu) {
		return (direction * direction_mul) + origin;
	}

	Vec3 CeilFloorAuto(Vec3 v) restrict(amp, cpu) {
		if (direction.x > 0) v.x = ceilf(v.x);
		else v.x = floorf(v.x);

		if (direction.y > 0) v.y = ceilf(v.y);
		else v.y = floorf(v.y);

		if (direction.z > 0) v.z = ceilf(v.z);
		else v.z = floorf(v.z);

		return v;
	}

	Vec3 ErrToInf(Vec3 vec, float d_max) restrict(amp, cpu) {
		vec.x = vec.x > d_max || vec.x <= 0 ? INFINITY : vec.x;
		vec.y = vec.y > d_max || vec.y <= 0 ? INFINITY : vec.y;
		vec.z = vec.z > d_max || vec.z <= 0 ? INFINITY : vec.z;
		return vec;
	}

	Vec3 GetNextPoint(float d_max) restrict(amp, cpu) {
		Vec3 offset = GetPoint();
		offset = CeilFloorAuto(offset);

		Vec3 j = (offset - origin) / direction;

		j = ErrToInf(j, d_max);

		if (j.x <= j.y && j.x <= j.z) direction_mul = j.x;
		if (j.y <= j.x && j.y <= j.z) direction_mul = j.y;
		if (j.z <= j.x && j.z <= j.y) direction_mul = j.z;

		direction_mul += 0.001f;
		steps++;

		return GetPoint();
	}
};

#endif // !__SteppedRay
