#ifndef __Cube
#define __Cube
#include "Color.h"

enum CubeType {
	None,
	Solid
};

class Cube
{
public:
	CubeType type = None;
	Color mainCol;

	Cube() restrict(amp, cpu) {}

	Cube(CubeType _type, Color _mainCol) restrict(amp, cpu) {
		type = _type;
		mainCol = _mainCol;
	}
};
#endif
