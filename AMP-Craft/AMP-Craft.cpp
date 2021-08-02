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

	initWindow(argc, argv);
}