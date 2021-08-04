#ifndef __Renderer
#define __Renderer
#include "World.h"
#include "RayCaster.h"
#include "Color.h"
class Renderer
{
public:
	RayCaster caster;
	World world;

	Color* RenderRays() {
		SteppedRay* rays = caster.CreateAllViewRays();
		Color* View = new Color[caster.view_height * caster.view_width];

		SteppedRay* ray;
		Color* pixel;
		Vec3 currentCube;

		for (unsigned int vx = 0, vy = 0; vy < caster.view_height;) {
			ray = &(rays[(vy * caster.view_width) + vx]);
			pixel = &View[(vy * caster.view_width) + vx];

			while (ray->direction_mul < 10) {
				currentCube = ray->GetNextPoint();

				if (world.GetCube(currentCube.x, currentCube.y, currentCube.z).type == Solid) {
					pixel->R = UINT_MAX;
					pixel->G = UINT_MAX;
					pixel->B = UINT_MAX;
					break;
				}
			}

			vx++;
			if (vx == caster.view_width) {
				vx = 0; vy++;
			}
		}
		return View;
	}
};

#endif