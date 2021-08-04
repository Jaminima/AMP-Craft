#ifndef __SteppedRay
#define __SteppedRay
#include "Ray.h"

class SteppedRay :
	public Ray
{
public:
	float direction_mul = 1.0f;

	SteppedRay() :Ray(Vec3(), Vec3()) {}

	SteppedRay(Vec3 _origin, Vec3 _direction) : Ray(_origin, _direction) {
		_direction.ensureNormalised();
	}

	Vec3 GetPoint() {
		return (direction * direction_mul) + origin;
	}

	Vec3 CeilFloorAuto(Vec3 v) {
		if (direction.x > 0) v.x = ceilf(v.x);
		else v.x = floorf(v.x);

		if (direction.y > 0) v.y = ceilf(v.y);
		else v.y = floorf(v.y);

		if (direction.z > 0) v.z = ceilf(v.z);
		else v.z = floorf(v.z);

		return v;
	}

	Vec3 GetNextPoint() {
		Vec3 offset = GetPoint();
		offset = CeilFloorAuto(offset);

		Vec3 j = (offset - origin) / direction;

		if (j.x <= j.y && j.x <= j.z) direction_mul = j.x;
		if (j.y <= j.x && j.y <= j.z) direction_mul = j.y;
		if (j.z <= j.x && j.z <= j.y) direction_mul = j.z;

		direction_mul += 0.001f;

		return GetPoint();
	}
};

#endif // !__SteppedRay
