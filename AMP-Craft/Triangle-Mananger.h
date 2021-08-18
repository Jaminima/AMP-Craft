#ifndef __TriMan
#define __TriMan
#include <amp.h>
using namespace concurrency;

#include "Triangle.h"

#define MaxTriangles 1000

struct TriangleRegion {
	unsigned int start, end;
};

namespace Triangle_Manager {

	unsigned int activeTriangles = 0;

	array_view<Triangle, 1> triangleView(MaxTriangles);

	extent<1> GetTriangleExtent() {
		return extent<1>(activeTriangles);
	}

	void RegisterTriangle(Triangle t) {
		triangleView[activeTriangles] = t;
		activeTriangles++;
	}

	TriangleRegion RegisterTriangles(Triangle* ts, unsigned int size) {
		TriangleRegion region;
		region.start = activeTriangles;

		for (unsigned int i = 0; i < size; i++) RegisterTriangle(ts[i]);

		region.end = activeTriangles;
		return region;
	}


}

#endif