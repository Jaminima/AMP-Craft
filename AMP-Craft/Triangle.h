#ifndef __Triangle
#define __Triangle
#include "Vec3.h"

class Triangle {
public:
	Vec3 P1, P2, P3;

	Triangle() restrict(amp,cpu) {

	}

	Triangle(Vec3 _P1, Vec3 _P2, Vec3 _P3) restrict(amp, cpu) {
		P1 = _P1;
		P2 = _P2;
		P3 = _P3;
	}
};

#endif // !__Triangle
