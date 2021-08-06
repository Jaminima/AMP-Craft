#ifndef __World
#define __World
#include "Cube.h"

#include <amp.h>
using namespace concurrency;

#define blocks_wide  50
#define blocks_long  50
#define blocks_deep  50

Cube GetCube(unsigned int x, unsigned int y, unsigned int z, array_view<Cube, 3> world_arr) restrict(amp, cpu) {
	if (x >= 0 && y >= 0 && z >= 0 && x < blocks_wide && y < blocks_deep && z < blocks_long) {
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
		cubeSet = new Cube[blocks_deep * blocks_long * blocks_wide];
		array_view<Cube, 3> world_arr(blocks_deep, blocks_long, blocks_wide, cubeSet);

		for (unsigned int x = 0, y = 0, z = 0; y < blocks_deep;) {
			SetCube(x, y, z, world_arr, Cube());
			x++;
			if (x == blocks_wide) { x = 0; z++; }
			if (z == blocks_long) { z = 0; y++; }
		}
	}
};
#endif