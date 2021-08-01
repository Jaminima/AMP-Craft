#ifndef __World
#define __World
#include "Cube.h"
class World
{
public:
	unsigned int blocks_wide = 10, blocks_long = 10, blocks_deep = 10;
	Cube* cubeSet;

	World() {
		cubeSet = new Cube[blocks_deep, blocks_long, blocks_wide];
	}

	Cube GetCube(unsigned int x, unsigned int y, unsigned int z) {
		return cubeSet[y, z, x];
	}

	void SetCube(unsigned int x, unsigned int y, unsigned int z, Cube c) {
		cubeSet[y, z, x] = c;
	}
};

#endif