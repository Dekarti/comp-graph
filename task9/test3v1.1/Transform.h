#include <array>
#include <vector>

#pragma once

#define M 3
#define N 4

typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;

typedef std::tr1::array<float, N> vec3D;
typedef std::tr1::array<vec3D, N> mat3D;


extern mat T;
extern std::vector<mat> matrices;

value struct point {
	point(float _x, float _y) { x = _x; y = _y; } 
	float x;
	float y;
};

value struct point3D {
	point3D(float _x, float _y, float _z) { x = _x; y = _y; z = _z; } 
	float x;
	float y;
	float z;
};

typedef System::Collections::Generic::List<point> polygon;
typedef System::Collections::Generic::List<point3D> polygon3D;

value struct line {
	point start, end;
	System::String^ name;
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

void times(mat3D a, mat3D b, mat3D &c);
void timesMatVec(mat3D a, vec3D b, vec3D &c);
void set(mat3D a, mat3D &b);
void point2vec(point3D a, vec3D &b);
void vec2point(vec3D a, point3D &b);
void makeHomogenVec(float x, float y, float z, vec3D &c);
void unit(mat3D &a);
void move(float Tx, float Ty, float Tz, mat3D &c);
void rotate(float phi, mat3D &c);
void scale(float S, mat3D &c);

vec3D operator+ (vec3D &a, vec3D &b);
vec3D operator- (vec3D &a, vec3D &b);
vec3D operator* (float k , vec3D a);
vec3D normalize (vec3D &a);

void LookAt (point3D eye, point3D center, point3D up, mat3D &c);

void Ortho (float Vx, float Vy, float near, float far, mat3D &c);
void Frustrum (float Vx, float Vy, float near, float far, mat3D &c);
void Perspective (float fovy, float aspect, float near, float far, mat3D &c);

void set (point3D a, point &b);