#ifndef __RayCaster
#define __RayCaster
#include "SteppedRay.h"

class RayCaster
{
public:
	float angleToRadians(float angle) {
		return angle * 3.14159265358979323f / 180.0f;
	}

	float fov_angle = 90, fov_radians = angleToRadians(fov_angle), fov_half_angle = fov_angle / 2;

	float fov_sin_max = sin(angleToRadians(fov_half_angle)),
		fov_cos_max = cos(angleToRadians(fov_half_angle));

	unsigned int view_width = 800, view_height = 600;

	float half_vw = view_width / 2, half_vh = view_height / 2;

	SteppedRay CreateRay(unsigned int vx, unsigned int vy, Vec3 origin) {
		float vx_angle = -(fov_sin_max * (1 - (vx / half_vw)));
		float vy_angle = -(fov_sin_max * (1 - (vy / half_vh)));

		return SteppedRay(origin, Vec3(vx_angle, vy_angle, 1));
	}

	SteppedRay* CreateAllViewRays(Vec3 origin) {
		SteppedRay* rays = new SteppedRay[view_height * view_width];
		for (unsigned int vx = 0, vy = 0; vy < view_height;) {
			rays[(vy*view_width) + vx] = CreateRay(vx, vy, origin);

			vx++;
			if (vx == view_width) { vx = 0; vy++; }
		}
		return rays;
	}
};

#endif