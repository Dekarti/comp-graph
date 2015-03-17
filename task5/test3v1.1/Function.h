#include <cmath>

#define EPS 0.1

float f(float x) {
	return 1 / sin(x);
}

bool fexists(float x) {
	return (abs(sin(x)) < EPS)? 0 : 1;
}

