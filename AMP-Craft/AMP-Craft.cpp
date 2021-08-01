#include <iostream>
#include "SteppedRay.h"

int main()
{
    std::cout << "Hello World!\n";
    SteppedRay r(Vec3(0,0,0),Vec3(0.2f,0.5f, 0.7f));
    Vec3 p;

    while (true) {
        p = r.GetNextPoint();
    }
}
