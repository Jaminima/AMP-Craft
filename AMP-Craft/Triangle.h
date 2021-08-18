#ifndef __Triangle
#define __Triangle
#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

#define Epsilon 0.0000001f

class Triangle {
public:
	Vec3 P1, P2, P3;
	Color mainColor;
	unsigned int textureId=INFINITE;

	Triangle() restrict(amp,cpu) {

	}

	Triangle(Vec3 _P1, Vec3 _P2, Vec3 _P3) restrict(amp, cpu) {
		P1 = _P1;
		P2 = _P2;
		P3 = _P3;
		mainColor = Color(255, 255, 255);
	}

	Triangle(Vec3 _P1, Vec3 _P2, Vec3 _P3, Color _c) restrict(amp, cpu) {
		P1 = _P1;
		P2 = _P2;
		P3 = _P3;
		mainColor = _c;
	}

	Triangle(Vec3 _P1, Vec3 _P2, Vec3 _P3, unsigned int _textureId) restrict(amp, cpu) {
		P1 = _P1;
		P2 = _P2;
		P3 = _P3;
		textureId = _textureId;
	}

	//Using Möller–Trumbore intersection algorithm https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
	float ComputeT(Ray r) restrict(amp, cpu) {
		Vec3 edge1 = P2 - P1,
			edge2 = P3 - P1;

		Vec3 h = r.direction.crossProduct(edge2);

		float a = edge1.dotProduct(h);

		if (a > -Epsilon && a < Epsilon)
			return false;

		float f = 1.0f / a;
		Vec3 s = r.origin - P1;

		float u = f * s.dotProduct(h);

		if (u < 0 || u>1)
			return false;

		Vec3 q = s.crossProduct(edge1);
		float v = f * r.direction.dotProduct(q);

		if (v < 0 || u + v>1)
			return false;

		float t = f * edge2.dotProduct(q);
		return t;
	}

	bool ValidT(float t) restrict(amp, cpu) {
		return t > Epsilon;
	}

	Vec3 GetIntersectFromT(float t, Ray r) restrict(amp, cpu) {
		return r.origin + r.direction * t;
	}
};

#endif // !__Triangle
