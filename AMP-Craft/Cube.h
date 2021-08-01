#ifndef __Cube
#define __Cube
enum CubeType {
	None,
	Solid
};

class Cube
{
public:
	CubeType type = Solid;
};
#endif
