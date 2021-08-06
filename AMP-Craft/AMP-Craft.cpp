#include <iostream>
#include "Window.h"

int main(int argc, char** argv)
{
	std::cout << "Hello World!\n";
	/*SteppedRay r(Vec3(0, 0, 0), Vec3(0.2f, 0.5f, 0.7f));
	Vec3 p;

	while (true) {
		p = r.GetNextPoint();
	}*/

	/*RayCaster r;
	SteppedRay* rays = r.CreateAllViewRays();*/

	array_view<Cube, 3> world_arr(blocks_deep, blocks_long, blocks_wide, Renderer::world.cubeSet);

	Cube c;
	c.type = Solid;
	SetCube(2, 2, 8, world_arr, c);
	SetCube(4, 2, 8, world_arr, c);
	SetCube(6, 2, 8, world_arr, c);

	SetCube(1, 5, 8, world_arr, c);
	SetCube(3, 5, 8, world_arr, c);
	SetCube(5, 5, 8, world_arr, c);

	initWindow(argc, argv);
}