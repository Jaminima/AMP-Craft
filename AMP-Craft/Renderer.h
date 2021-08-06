#ifndef __Renderer
#define __Renderer
#include "World.h"
#include "RayCaster.h"
#include "Color.h"
#include "Camera.h"

#include <iostream>

#include <amp.h>
using namespace concurrency;

namespace Renderer
{
	World world;
	array_view<Cube, 3> world_arr = array_view<Cube,3>(blocks_deep, blocks_long, blocks_wide, world.cubeSet);

	Color* View = new Color[input_main_camera.view_height * input_main_camera.view_width];

	void RenderRay(index<2> idx, array_view<Color, 2> _view_arr, array_view<Cube, 3> _world_arr, Camera cam) restrict(amp, cpu) {
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

	void RenderRays(Camera cam) {

		array_view<Cube, 3> _world_arr = world_arr;
		array_view<Color, 2> _view_arr = array_view<Color, 2>(cam.view_height, cam.view_width, View);

		parallel_for_each(
			_view_arr.extent,
			[=](index<2> idx)restrict(amp) {
				RenderRay(idx, _view_arr, _world_arr, cam);
			}
		);

		/*for (unsigned int x = 0, y = 0; y < cam.view_height;) {
			RenderRay(index<2>(y, x), _view_arr, _world_arr, cam);
			x++;
			if (x == cam.view_width) { x = 0; y++; }
		}*/

		_view_arr.synchronize();
	}
};

#endif