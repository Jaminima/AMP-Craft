#ifndef __Renderer
#define __Renderer
#include "World.h"
#include "RayCaster.h"
#include "Color.h"
#include "Camera.h"

#include <iostream>

#include <amp.h>
using namespace concurrency;

#define d_max 40

namespace Renderer
{
	World world;
	array_view<Cube, 3> world_arr = array_view<Cube, 3>(chunk_height, chunk_length, chunk_width, world.cubeSet);

	Color* View = new Color[input_main_camera.view_height * input_main_camera.view_width];
	array_view<Color, 2> view_arr = array_view<Color, 2>(input_main_camera.view_height, input_main_camera.view_width, View);

	float absf(float f)restrict(amp, cpu) {
		if (f > 0) return f;
		else return -1 * f;
	}

	void RenderRay(index<2> idx, array_view<Color, 2> _view_arr, array_view<Cube, 3> _world_arr, Camera cam) restrict(amp, cpu) {
		SteppedRay r = RayCaster::CreateRay(idx[1], idx[0], cam);
		Vec3 currentCube;
		Cube cubeObj;

		while (r.direction_mul < d_max && r.steps < d_max * 3) {
			currentCube = r.GetNextPoint(d_max);
			cubeObj = GetCube(currentCube.x, currentCube.y, currentCube.z, _world_arr);

			if (cubeObj.type != None) {
				_view_arr[idx[0]][idx[1]] = cubeObj.mainCol;
				break;
			}
		}
		if (r.direction_mul >= d_max) {
			_view_arr[idx[0]][idx[1]] = Color();
		}
	}

	completion_future RenderRays(Camera cam) {
		array_view<Cube, 3> _world_arr = world_arr;
		array_view<Color, 2> _view_arr = view_arr;

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

		return _view_arr.synchronize_async();
	}
};

#endif