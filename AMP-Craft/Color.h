#ifndef __Color
#define __Color
#include <iostream>
class Color
{
public:
	//unsigned int R, G, B, A;

	unsigned int rgba = 0x0F000000;

	void SetR(unsigned int r) restrict(amp, cpu) { rgba = rgba | ((r & 0xFF)); }
	void SetG(unsigned int g) restrict(amp, cpu) { rgba = rgba | ((g & 0xFF) << 8); }
	void SetB(unsigned int b) restrict(amp, cpu) { rgba = rgba | ((b & 0xFF) << 16); }

	unsigned int GetR()restrict(amp, cpu) { return (rgba) & 0xFF; }
	unsigned int GetG()restrict(amp, cpu) { return (rgba >> 8) & 0xFF; }
	unsigned int GetB()restrict(amp, cpu) { return (rgba >> 16) & 0xFF; }

	Color() restrict(amp, cpu) {
	}

	Color(unsigned int r, unsigned int g, unsigned int b) restrict(amp, cpu)
	{
		rgba |= ((b & 0xFF) << 16) | ((g & 0xFF) << 8) | ((r & 0xFF));
	}
};

#endif