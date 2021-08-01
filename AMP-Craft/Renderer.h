#ifndef __Renderer
#define __Renderer
#include "World.h"
#include "RayCaster.h"
class Renderer
{
public:
	RayCaster caster;
	World world;

	bool* RenderRays() {
		SteppedRay* rays = caster.CreateAllViewRays();
		bool* view = new bool[caster.view_height, caster.view_width];

		for (unsigned int vx = 0, vy = 0; vy < caster.view_height;) {
			SteppedRay* ray = &rays[vy, vx];
			Vec3 currentCube;

			while (ray->direction_mul < 50) {
				currentCube = ray->GetNextPoint();

				if (world.GetCube(currentCube.x, currentCube.y, currentCube.z).type != None) {
					view[vy, vx] = true;
					break;
				}
			}

			vx++;
			if (vx == caster.view_width) { vx = 0; vy++; }
		}
		return view;
	}
};

#endif