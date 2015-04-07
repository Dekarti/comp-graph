#include <array>
#include <vector>

#pragma once

#define M 3

typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;


extern mat T;
extern std::vector<mat> matrices;

value struct point {
	float x;
	float y;
	point(float _x, float _y) { x = _x; y = _y; }
	
};

typedef System::Collections::Generic::List<point> polygon;

value struct line {
	point start, end;
	System::String^ name;
};

value struct ternary {
	float x1;
	float y2;
	float dx;
};

void times(mat a, mat b, mat &c);
void timesMatVec(mat a, vec b, vec &c);
void set(mat a, mat &b);
void point2vec(point a, vec &b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec &c);
void unit(mat &a);
void move(float Tx, float Ty, mat &c);
void rotate(float phi, mat &c);
void scale(float S, mat &c);
void mirror(bool axis, mat &c);
void rotateAbout(float phi, float x, float y, mat &c);
void stretch(float Sx, float Sy, mat &c);
void frame (float Vx, float Vy, float Vcx, float Vcy,
	        float Wx, float Wy, float Wcx, float Wcy,
		    mat &c);