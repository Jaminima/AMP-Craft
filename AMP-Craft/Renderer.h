#ifndef __Renderer
#define __Renderer
#include "RayCaster.h"
#include "Color.h"
#include "Camera.h"

#include "Triangle-Mananger.h"

#include <iostream>

#include <amp.h>
using namespace concurrency;

#define d_max 40

namespace Renderer
{
	Color* View = new Color[input_main_camera.view_height * input_main_camera.view_width];
	array_view<Color, 2> view_arr = array_view<Color, 2>(input_main_camera.view_height, input_main_camera.view_width, View);

	void RenderRay(index<2> idx, array_view<Color, 2> _view_arr, array_view<Triangle, 1> _world_arr, Camera cam) restrict(amp, cpu) {
		Ray r = RayCaster::CreateRay(idx[1], idx[0], cam);
		Vec3 currentCube;
		

	}

	completion_future RenderRays(Camera cam) {
		array_view<Triangle, 1> _tri_arr = Triangle_Manager::triangleView;
		array_view<Color, 2> _view_arr = view_arr;

		parallel_for_each(
			_view_arr.extent,
			[=](index<2> idx)restrict(amp) {
				RenderRay(idx, _view_arr, _tri_arr, cam);
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