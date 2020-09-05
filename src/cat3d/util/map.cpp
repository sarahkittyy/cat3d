#include "cat3d/util/map.hpp"

namespace cat3d::util {

template <typename Number>
Number map(Number v, Number lo, Number hi, Number newlo, Number newhi) {
	double dv(v);
	double dlo(lo);
	double dhi(hi);
	double dnewlo(newlo);
	double dnewhi(newhi);

	double through = (dv - dlo) / (dhi - dlo);
	return Number((through * (dnewhi - dnewlo)) + newlo);
}

template float map(float, float, float, float, float);

template int map(int, int, int, int, int);

template unsigned int map(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

template char map(char, char, char, char, char);

template unsigned char map(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);

template short map(short, short, short, short, short);

template unsigned short map(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);

template double map(double, double, double, double, double);
}