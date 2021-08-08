#ifndef __Cube
#define __Cube
enum CubeType {
	None,
	Solid
};

class Cube
{
public:
	CubeType type = None;

	Cube() restrict(amp, cpu) {}
};
#endif
