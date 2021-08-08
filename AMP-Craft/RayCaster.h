#ifndef __RayCaster
#define __RayCaster
#include "SteppedRay.h"
#include "Camera.h"

namespace RayCaster
{
	SteppedRay CreateRay(unsigned int vx, unsigned int vy, Camera cam) restrict(amp, cpu) {
		float vx_angle = -(cam.fov_sin_max * (1 - (vx / cam.half_vw)));
		float vy_angle = -(cam.fov_sin_max * (1 - (vy / cam.half_vh)));

		return SteppedRay(cam.Position, cam.RotateDirection(Vec3(vx_angle, vy_angle, 1)));
	}

	SteppedRay* CreateAllViewRays(Camera cam) {
		SteppedRay* rays = new SteppedRay[cam.view_height * cam.view_width];
		for (unsigned int vx = 0, vy = 0; vy < cam.view_height;) {
			rays[(vy * cam.view_width) + vx] = CreateRay(vx, vy, cam);

			vx++;
			if (vx == cam.view_width) { vx = 0; vy++; }
		}
		return rays;
	}
};

#endif