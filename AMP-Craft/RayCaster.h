#ifndef __RayCaster
#define __RayCaster
#include "Ray.h"
#include "Camera.h"

namespace RayCaster
{
	Ray CreateRay(unsigned int vx, unsigned int vy, Camera cam) restrict(amp, cpu) {
		float vx_angle = -(cam.fov_sin_max * (1 - (vx / cam.half_vw)));
		float vy_angle = -(cam.fov_sin_max * (1 - (vy / cam.half_vh)));

		return Ray(cam.Position, cam.RotateDirection(Vec3(vx_angle, vy_angle, 1)));
	}

	Ray* CreateAllViewRays(Camera cam) {
		Ray* rays = new Ray[cam.view_height * cam.view_width];
		for (unsigned int vx = 0, vy = 0; vy < cam.view_height;) {
			rays[(vy * cam.view_width) + vx] = CreateRay(vx, vy, cam);

			vx++;
			if (vx == cam.view_width) { vx = 0; vy++; }
		}
		return rays;
	}
};

#endif