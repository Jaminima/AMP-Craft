#ifndef __Color
#define __Color
#include <iostream>
class Color
{
public:
	unsigned int R, G, B, A;

	Color() {
		R = 0;
		G = 0;
		B = 0;
		A = UINT_MAX;
	}
};

#endif