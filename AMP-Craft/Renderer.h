#ifndef __Renderer
#define __Renderer
#include "World.h"
#include "RayCaster.h"
#include "Color.h"
#include "Camera.h"

#include <amp.h>
using namespace concurrency;

class Renderer
{
public:
	World world;
	Camera camera;

	Color* RenderRays() {
		Color* View = new Color[camera.view_height * camera.view_width];

		Camera cam = camera;

		array_view<Color, 2> view_arr(camera.view_height, camera.view_width, View);
		array_view<Cube, 3> world_arr(blocks_deep, blocks_long, blocks_wide, world.cubeSet);

		parallel_for_each(
			view_arr.extent,
			[=](index<2> idx)restrict(amp) {
				SteppedRay r = RayCaster::CreateRay(idx[1], idx[0], cam);
				Vec3 currentCube;

				while (r.direction_mul < 20) {
					currentCube = r.GetNextPoint();

					if (GetCube(currentCube.x, currentCube.y, currentCube.z, world_arr).type == Solid) {
						view_arr[idx[0]][idx[1]].R = UINT_MAX;
						view_arr[idx[0]][idx[1]].G = UINT_MAX;
						view_arr[idx[0]][idx[1]].B = UINT_MAX;
					}

				}
			}
		);

		view_arr.synchronize();

		return View;

		/*SteppedRay* ray;
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
		}*/
	}
};

#endif