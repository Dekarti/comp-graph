//#include <array>
//#include <vector>
//
//#pragma once
//
//#define M 3
//#define N 4
//
//typedef std::tr1::array<float, M> vec;
//typedef std::tr1::array<vec, M> mat;
//
//typedef std::tr1::array<float, N> vec3D;
//typedef std::tr1::array<vec3D, N> mat3D;
//
//
//extern mat3D T;
//extern mat L;
//extern std::vector<mat> matrices;
//
//value struct point {
//	point(float x, float y) : x(x), y(y) { }
//	float x;
//	float y;
//};
//
//value struct point3D {
//	point3D(float x, float y, float z) : x(x), y(y), z(z) { } 
//	float x;
//	float y;
//	float z;
//};
//
//typedef System::Collections::Generic::List<point> polygon;
//typedef System::Collections::Generic::List<point3D> polygon3D;
//
//value struct line {
//	point start, end;
//	System::String^ name;
//};
//
//void times(mat a, mat b, mat &c);
//void timesMatVec(mat a, vec b, vec &c);
//void set(mat a, mat &b);
//void point2vec(point a, vec &b);
//void vec2point(vec a, point &b);
//void makeHomogenVec(float x, float y, vec &c);
//void unit(mat &a);
//void move(float Tx, float Ty, mat &c);
//void rotate(float phi, mat &c);
//void scale(float S, mat &c);
//void mirror(bool axis, mat &c);
//void rotateAbout(float phi, float x, float y, mat &c);
//void stretch(float Sx, float Sy, mat &c);
//void frame (float Vx, float Vy, float Vcx, float Vcy,
//	        float Wx, float Wy, float Wcx, float Wcy,
//		    mat &c);
//
//void times(mat3D a, mat3D b, mat3D &c);
//void timesMatVec(mat3D a, vec3D b, vec3D &c);
//void set(mat3D a, mat3D &b);
//void point2vec(point3D a, vec3D &b);
//void vec2point(vec3D a, point3D &b);
//void makeHomogenVec(float x, float y, float z, vec3D &c);
//void unit(mat3D &a);
//void move(float Tx, float Ty, float Tz, mat3D &c);
//void rotate (point3D n, float phi, mat3D &c);
//void scale(float S, mat3D &c);
//
//vec3D operator+ (vec3D &a, vec3D &b);
//vec3D operator- (vec3D &a, vec3D &b);
//vec3D operator* (float k , vec3D a);
//vec3D normalize (vec3D &a);
//point3D normalize (point3D &a);
//void crossProduct(vec3D a, vec3D b, vec3D &c);
//void crossProduct(point3D a, point3D b, point3D &c);
//
//void LookAt (point3D eye, point3D center, point3D up, mat3D &c);
//
//void Ortho (float Vx, float Vy, float near, float far, mat3D &c);
//void Frustrum (float Vx, float Vy, float near, float far, mat3D &c);
//void Perspective (float fovy, float aspect, float near, float far, mat3D &c);
//
//void set (point3D a, point &b);
#include <array>
#include <vector>

#define M 3
#define M3D 4

typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;

typedef std::tr1::array<float, M3D> vec3D;
typedef std::tr1::array<vec3D, M3D> mat3D;

extern mat L;
extern mat3D T;

value struct point {
	float x, y;

	point(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

value struct point3D {
	float x, y, z;

	point3D(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

value struct line {
	point start, end;
	System::String^ name;

	line(point start, point end) {
		this->start = start;
		this->end = end;
		this->name = "";
	}
};

value struct line3D {
	point3D start, end;
	System::String^ name;

	line3D(point3D start, point3D end) {
		this->start = start;
		this->end = end;
		this->name = "";
	}
};

typedef System::Collections::Generic::List<point> polygon;
typedef System::Collections::Generic::List<point3D> polygon3D;

void times(mat a, mat b, mat& c);
void timesMatVec(mat a, vec b, vec& c);
void set(mat a, mat& b);
void point2vec(point a, vec& b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec& c);
void unit(mat& a);
void move(float Tx, float Ty, mat& c);
void rotate(float phi, float x, float y, mat& c);
void scale(float Sx, float Sy, mat& c);
void reflect(bool xAxis, bool yAxis, mat& c);
void frame (float Vx, float Vy, float Vcx, float Vcy,
			float Wx, float Wy, float Wcx, float Wcy,
			mat& c);

void times(mat3D a, mat3D b, mat3D &c);
void timesMatVec(mat3D a, vec3D b, vec3D &c);
void set(mat3D a, mat3D &b);
void point2vec(point3D a, vec3D &b);
void vec2point(vec3D a, point3D &b);
void makeHomogenVec(float x, float y, float z, vec3D &c);
void unit(mat3D &a);
void move(float Tx, float Ty, float Tz, mat3D &c);
void rotate(point3D n, float phi, mat3D &c);
void scale(float Sx, float Sy, float Sz, mat3D &c);

void sum(mat3D a, mat3D b, mat3D& c);
void mult(mat3D a, float k, mat3D& c);
void sum(vec3D a, vec3D b, vec3D& c);
void sum(point3D a, point3D b, point3D& c);
void sub(vec3D a, vec3D b, vec3D& c);
void mult(vec3D a, float k, vec3D& c);
void normalize(vec3D& v);
float vecLength(vec3D v);
void vecMult(vec3D a, vec3D b, vec3D& c);
void set(point3D a, point &b);
void calculateAxes(point3D eye, point3D center, point3D up, vec3D& x, vec3D& y, vec3D& z); 

void LookAt(point3D eye, point3D center, point3D up, mat3D &c);

void Ortho(float Vx, float Vy, float near, float far, mat3D &c);
void Frustrum(float Vx, float Vy, float near, float far, mat3D &c);
void Perspective(float fovy, float aspect, float near, float far, mat3D &c);

float round(float x, int n);