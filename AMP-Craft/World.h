#ifndef __World
#define __World
#include "Cube.h"

#include <amp.h>
using namespace concurrency;

#define chunk_width  1024
#define chunk_height  16
#define chunk_length  1024

Cube GetCube(unsigned int x, unsigned int y, unsigned int z, array_view<Cube, 3> world_arr) restrict(amp, cpu) {
	if (x >= 0 && y >= 0 && z >= 0 && x < chunk_width && y < chunk_height && z < chunk_length) {
		return world_arr[y][z][x];
	}
	else return Cube();
}

void SetCube(unsigned int x, unsigned int y, unsigned int z, array_view<Cube, 3> world_arr, Cube c) restrict(amp, cpu) {
	world_arr[y][z][x] = c;
}

class World
{
public:

	Cube* cubeSet;

	World() {
		cubeSet = new Cube[chunk_width * chunk_height * chunk_length];
		array_view<Cube, 3> _world_arr(chunk_height, chunk_length, chunk_width, cubeSet);

		parallel_for_each(
			_world_arr.extent,
			[=](index<3> idx) restrict(amp) {
				if (idx[0] < chunk_height / 2) _world_arr[idx] = Cube(Solid, Color(255,255*(idx[1]%2),255 * (idx[2] % 2)));
			}
		);

		_world_arr.synchronize();

		/*for (unsigned int x = 0, y = 0, z = 0; y < chunk_height;) {
			if (y > chunk_height/2) SetCube(x, y, z, world_arr, Cube());
			else SetCube(x, y, z, world_arr, Cube(Solid));
			x++;
			if (x == chunk_width) { x = 0; z++; }
			if (z == chunk_length) { z = 0; y++; }
		}*/
	}
};
#endif