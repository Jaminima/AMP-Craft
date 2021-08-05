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
	array_view<Cube, 3> world_arr = array_view<Cube,3>(blocks_deep, blocks_long, blocks_wide, world.cubeSet);

	Color* View = new Color[camera.view_height * camera.view_width];
	array_view<Color, 2> view_arr = array_view<Color, 2>(camera.view_height, camera.view_width, View);

	void RenderRays() {

		Camera cam = camera;

		array_view<Cube, 3> _world_arr = world_arr;
		array_view<Color, 2> _view_arr = view_arr;

		parallel_for_each(
			view_arr.extent,
			[=](index<2> idx)restrict(amp) {
				SteppedRay r = RayCaster::CreateRay(idx[1], idx[0], cam);
				Vec3 currentCube;

				while (r.direction_mul < 20) {
					currentCube = r.GetNextPoint();

					if (GetCube(currentCube.x, currentCube.y, currentCube.z, _world_arr).type == Solid) {
						_view_arr[idx[0]][idx[1]].R = UINT_MAX;
						_view_arr[idx[0]][idx[1]].G = UINT_MAX;
						_view_arr[idx[0]][idx[1]].B = UINT_MAX;
						break;
					}
				}
				if (r.direction_mul >= 20) {
					_view_arr[idx[0]][idx[1]].R = 0;
					_view_arr[idx[0]][idx[1]].G = 0;
					_view_arr[idx[0]][idx[1]].B = 0;
				}
			}
		);

		view_arr.synchronize();

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