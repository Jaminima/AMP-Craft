#ifndef __World
#define __World
#include "Cube.h"
class World
{
public:
	unsigned int blocks_wide = 50, blocks_long = 50, blocks_deep = 50;
	Cube* cubeSet;

	World() {
		cubeSet = new Cube[blocks_deep * blocks_long * blocks_wide];

		for (unsigned int x = 0, y = 0, z = 0; y < blocks_deep;) {
			SetCube(x, y, z, Cube());
			x++;
			if (x == blocks_wide) { x = 0; z++; }
			if (z == blocks_long) { z = 0; y++; }
		}
	}

	int getIndex(unsigned int x, unsigned int y, unsigned int z) {
		int idx = ((y * blocks_long) + z) * blocks_wide + x;
		return idx;
	}

	Cube GetCube(unsigned int x, unsigned int y, unsigned int z) {
		if (x >= 0 && y >= 0 && z >= 0 && x < blocks_wide && y < blocks_deep && z < blocks_long) {
			return cubeSet[getIndex(x,y,z)];
		}
		else return Cube();
	}

	void SetCube(unsigned int x, unsigned int y, unsigned int z, Cube c) {
		cubeSet[getIndex(x, y, z)] = c;
	}
};

#endif