#ifndef __World
#define __World
#include "Cube.h"

#include <amp.h>
using namespace concurrency;

#define chunk_width  16
#define chunk_height  16
#define chunk_length  16

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
		array_view<Cube, 3> world_arr(chunk_height, chunk_length, chunk_width, cubeSet);

		for (unsigned int x = 0, y = 0, z = 0; y < chunk_height;) {
			SetCube(x, y, z, world_arr, Cube());
			x++;
			if (x == chunk_width) { x = 0; z++; }
			if (z == chunk_length) { z = 0; y++; }
		}
	}
};
#endif