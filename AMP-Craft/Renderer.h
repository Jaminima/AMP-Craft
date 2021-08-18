#ifndef __Renderer
#define __Renderer
#include "RayCaster.h"
#include "Color.h"
#include "Camera.h"

#include "Triangle-Mananger.h"
#include "TextureManager.h"

#include <iostream>

#include <amp.h>
using namespace concurrency;

namespace Renderer
{
	Color* View = new Color[input_main_camera.view_height * input_main_camera.view_width];
	array_view<Color, 2> view_arr = array_view<Color, 2>(input_main_camera.view_height, input_main_camera.view_width, View);

	Color RenderRay(index<2> idx, array_view<Color, 3> _texture_arr, array_view<Triangle, 1> _tri_arr, unsigned int tri_size, Camera cam) restrict(amp, cpu) {
		Ray r = RayCaster::CreateRay(idx[1], idx[0], cam);

		float closestT = INFINITY;
		unsigned int closestIDX = INFINITE;
		
		for (unsigned int i = 0; i < tri_size; i++) {
			Triangle tri = _tri_arr[i];
			float t = tri.ComputeT(r);
			if (tri.ValidT(t) && t < closestT) {
				closestIDX = i;
				closestT = t;
			}
		}

		if (closestIDX == INFINITE) return Color(0, 0, 0);
		else {
			Triangle tri = _tri_arr[closestIDX];
			if (tri.textureId != INFINITE) {
				Vec3 p = tri.GetIntersectFromT(closestT, r);

				Vec3 diff = tri.P3 - tri.P2, diffAlt = tri.P3 - tri.P1;

				if (diff.x < diffAlt.x) diff.x = diffAlt.x;
				if (diff.y < diffAlt.y) diff.y = diffAlt.y;
				if (diff.z < diffAlt.z) diff.z = diffAlt.z;

				Vec3 r = tri.P3 - p;
				Vec3 ra = r / diff;

				return _texture_arr[tri.textureId][ra.y * 100][ra.x * 100];
			}
			else return tri.mainColor;
		}
	}

	completion_future RenderRays(Camera cam) {
		array_view<Triangle, 1> _tri_arr = Triangle_Manager::triangleView;
		array_view<Color, 2> _view_arr = view_arr;
		array_view<Color, 3> _texture_arr = Texture_Manager::texture_arr;
		unsigned int activeTriangles = Triangle_Manager::activeTriangles;

		parallel_for_each(
			_view_arr.extent,
			[=](index<2> idx)restrict(amp) {
				_view_arr[idx] = RenderRay(idx, _texture_arr, _tri_arr,  activeTriangles, cam);
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