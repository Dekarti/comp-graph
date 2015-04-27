//#pragma once
//#include "stdafx.h"
//#include "Transform.h"
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <math.h>
//
//
////mat T;
//mat3D T;
//mat L;
//std::vector<mat> matrices(0);
//
//void times(mat a, mat b, mat &c) {
//	for (int i = 0; i < M; i++) {
//		for (int j = 0; j < M; j++) {
//			float skalaar = 0;
//			for (int k = 0; k < M; k++)
//				skalaar += a[i][k] * b[k][j];
//			c[i][j] = skalaar;
//
//		}
//	}
//}
//
//void timesMatVec(mat a, vec b, vec &c) {
//	for (int i = 0; i < M; i++) {
//		float skalaar = 0;
//		for (int j = 0; j < M; j++)
//			skalaar += a[i][j] * b[j];
//		c[i] = skalaar;
//	}
//}
//
//void set(mat a, mat &b) {
//	for (int i = 0; i < M; i++)
//		for (int j = 0; j < M; j++)
//			b[i][j] = a[i][j];
//}
//
//void point2vec(point a, vec &b) {
//	b[0] = a.x; b[1] = a.y; b[2] = 1;
//}
//
//void vec2point(vec a, point &b) {
//	b.x = ((float)a[0]) / a[2];
//	b.y = ((float)a[1]) / a[2];
//}
//
//void makeHomogenVec(float x, float y, vec &c) {
//	c[0] = x;
//	c[1] = y;
//	c[2] = 1;
//}
//
//void unit(mat &a) {
//	for (int i = 0; i < M; i++) {
//		for (int j = 0; j < M; j++) {
//			if (i == j) a[i][j] = 1;
//			else a[i][j] = 0;
//		}
//	}
//}
//
//void move(float Tx, float Ty, mat &c) {
//	unit (c);
//	c[0][M-1] = Tx;
//	c[1][M-1] = Ty;
//}
//
//void rotate(float phi, mat &c) {
//	unit (c);
//	c[0][0] = cos(phi); c[0][1] = -sin(phi);
//	c[1][0] = sin(phi); c[1][1] = cos(phi);
//}
//
//void scale(float S, mat &c) {
//	unit (c);
//	c[0][0] = S; c[1][1] = S;
//}
//
//// true  - relative to the x-axis
//// false - relative to the y-axis
//void mirror(bool axis, mat &c) { 
//	unit (c);
//	(axis == true) ? c[1][1] = -1 : c[0][0] = -1; 
//}
//
//void rotateAbout(float phi, float x, float y, mat &c) {
//	unit(c);
//
//	c[0][0] = cos(phi); c[0][1] = -sin(phi);
//	c[1][0] = sin(phi); c[1][1] =  cos(phi);
//
//	c[0][M - 1] = -x * (cos(phi) - 1) + y * sin(phi);
//	c[1][M - 1] = -y * (cos(phi) - 1) - x * sin(phi);
//}
//
//void stretch(float Sx, float Sy, mat &c) {
//	unit(c);
//	c[0][0] = Sx; 
//	c[1][1] = Sy;
//}
//
//void frame (float Vx, float Vy, float Vcx, float Vcy,
//			float Wx, float Wy, float Wcx, float Wcy,
//			mat &c) {
//	unit(c);
//	mat R, T1;
//	move(-Vcx, -Vcy, R);
//	times(R, c, T1);
//	set(T1, c);
//	
//	float xs = Wx / Vx;
//	float ys = Wy / Vy;
//
//	stretch(xs, ys, R);
//	times(R, c, T1);
//	set(T1, c);
//
//	mirror(true, R);
//	times(R, c, T1);
//	set(T1, c);
//
//	move(Wcx, Wcy, R);
//	times(R, c, T1);
//	set(T1, c);
//}
//
///************** 3D FUNCTIONS DEFINITION ****************/
//
//void times(mat3D a, mat3D b, mat3D &c) {
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			float skalaar = 0;
//			for (int k = 0; k < N; k++)
//				skalaar += a[i][k] * b[k][j];
//			c[i][j] = skalaar;
//
//		}
//	}
//}
//
//void timesMatVec(mat3D a, vec3D b, vec3D &c) {
//	for (int i = 0; i < N; i++) {
//		float skalaar = 0;
//		for (int j = 0; j < N; j++)
//			skalaar += a[i][j] * b[j];
//		c[i] = skalaar;
//	}
//}
//
//void set(mat3D a, mat3D &b) {
//	for (int i = 0; i < N; i++)
//		for (int j = 0; j < N; j++)
//			b[i][j] = a[i][j];
//}
//
//void point2vec(point3D a, vec3D &b) {
//	b[0] = a.x;
//	b[1] = a.y;
//	b[2] = a.z;
//	b[3] = 1;
//}
//
//void vec2point(vec3D a, point3D &b) {
//	b.x = ((float)a[0]) / a[3];
//	b.y = ((float)a[1]) / a[3];
//	b.z = ((float)a[2]) / a[3];
//}
//void makeHomogenVec(float x, float y, float z, vec3D &c) {
//	c[0] = x;
//	c[1] = y;
//	c[2] = z;
//	c[3] = 1;
//}
//
//void unit(mat3D &a){
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			if (i == j) a[i][j] = 1;
//			else a[i][j] = 0;
//		}
//	}
//}
//
//void move(float Tx, float Ty, float Tz, mat3D &c) {
//	unit (c);
//	c[0][N-1] = Tx;
//	c[1][N-1] = Ty;
//	c[2][N-1] = Tz;
//}
//
//void rotate(point3D n, float phi, mat3D &c) {
//	float n1 = n.x;
//	float n2 = n.y;
//	float n3 = n.z;
//
//	c[0][0] = n1 * n1 + (1 - n1 * n1) * cos(phi);
//	c[0][1] = n1 * n2 * (1 - cos(phi)) - n3 * sin(phi);
//	c[0][2] = n1 * n3 * (1 - cos(phi)) + n2 * sin(phi);
//
//	c[1][0] = n1 * n2 * (1 - cos(phi)) + n3 * sin(phi);
//	c[1][1] = n2 * n2 + (1 - n2 * n2) * cos(phi);
//	c[1][2] = n2 * n3 * (1 - cos(phi)) - n1 * sin(phi);
//
//	c[2][0] = n1 * n3 * (1 - cos(phi)) - n2 * sin(phi);
//	c[2][1] = n2 * n3 * (1 - cos(phi)) + n1 * sin(phi);
//	c[2][2] = n3 * n3 + (1 - n3 * n3) * cos(phi);
//}
//
//void scale(float Sx, float Sy, float Sz, mat3D &c) {
//	unit(c);
//	c[0][0] = Sx; 
//	c[1][1] = Sy;
//	c[2][2] = Sz;
//}
///******************* ÂÑÏÎÌÎÃÀÒÅËÜÍÛÅ ÔÓÍÊÖÈÈ ********************/
//
//float lengthVec(vec3D a) {
//	return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
//}
//
//vec3D operator+ (vec3D &a, vec3D &b) {
//	vec3D c;
//	c[0] = a[0] + b[0];
//	c[1] = a[1] + b[1];
//	c[2] = a[2] + b[2];
//	c[3] = 1;
//	return c;
//}
//
//vec3D operator- (vec3D &a, vec3D &b) {
//	vec3D c;
//	c[0] = a[0] - b[0];
//	c[1] = a[1] - b[1];
//	c[2] = a[2] - b[2];
//	c[3] = 1;
//	return c;
//}
//vec3D operator* (float k , vec3D a) {
//	vec3D c;
//	c[0] = k * a[0];
//	c[1] = k * a[1];
//	c[2] = k * a[2];
//	c[3] = 1;
//	return c;
//}
//vec3D normalize (vec3D &a) {
//	vec3D c;
//	c[0] = a[0] / lengthVec(a);
//	c[1] = a[1] / lengthVec(a);
//	c[2] = a[2] / lengthVec(a);
//	c[3] = 1;
//	return c;
//}
//
//point3D normalize (point3D &a) {
//	vec3D b;
//	point2vec(a, b);
//	normalize(b);
//	vec2point(b, a);
//	return a;
//}
//
//void crossProduct(vec3D a, vec3D b, vec3D &c) {
//	c[0] = a[1] * b[2] - a[2] * b[1];
//    c[1] = a[2] * b[0] - a[0] * b[2];
//    c[2] = a[0] * b[1] - a[1] * b[0];
//}
//
//void crossProduct(point3D a, point3D b, point3D &c) {
//	c.x = a.y * b.z - a.z * b.y;
//    c.y = a.z * b.x - a.x * b.z;
//    c.z = a.x * b.y - a.y * b.x;
//}
//
///*****************************************************************/
//
//void LookAt (point3D eye, point3D center, point3D up, mat3D &c) {
//	mat3D R1, R2, V;
//	unit(R1);
//	move(-eye.x, -eye.y, -eye.z, R1);
//
//	vec3D s, p, u;
//	makeHomogenVec(eye.x, eye.y, eye.z, s);
//	makeHomogenVec(center.x, center.y, center.z, p);
//	makeHomogenVec(up.x, up.y, up.z, u);
//
//	vec3D Vps = s - p;
//	vec3D e1, e2, e3;
//	e3 = normalize(Vps);
//	crossProduct(u, e3, e1);
//	e1 = normalize(e1);
//	crossProduct(e3, e1, e2);
//	e2 = normalize(e2);
//
//	unit(R2);
//	R2[0][0] = e1[0]; R2[0][1] = e1[1]; R2[0][2] = e1[2];
//	R2[1][0] = e2[0]; R2[1][1] = e2[1]; R2[1][2] = e2[2];
//	R2[2][0] = e3[0]; R2[2][1] = e3[1]; R2[2][2] = e3[2];
//
//	unit(V);
//	times(R2, R1, V);
//	set(V, c);
//}
//
//void Ortho (float Vx, float Vy, float near, float far, mat3D &c) {
//	c[0][0] = 2 / Vx;
//	c[1][1] = 2 / Vy;
//	c[2][2] = 2 / (far - near);
//	c[2][3] = (far + near) / (far - near);
//}
//
//void set (point3D a, point &b) {
//	b.x = a.x;
//	b.y = a.y;
//}
//
//void Frustrum (float Vx, float Vy, float near, float far, mat3D &c) {
//	unit(c);
//	c[0][0] = near * 2 / Vx;
//	c[1][1] = near * 2 / Vy;
//	c[2][2] = (far + near) / (far - near);
//	c[3][3] = 0;
//	c[3][2] = -1;
//	c[2][3] = 2 * far * near / (far - near);
//}
//
//void Perspective (float fovy, float aspect, float near, float far, mat3D &c) {
//	float Vy = 2 * near * tan(fovy / 2);
//	float Vx = aspect * Vy;
//	Frustrum(Vx, Vy, near, far, c);
//}
#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>

std::vector<mat> matrices(0);

mat L;
mat3D T;

void times(mat a, mat b, mat& c) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			float skalaar = 0;
			for(int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec& c) {
	for(int i = 0; i < M; i++) {
		float skalaar = 0;
		for(int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat a, mat& b) {
	for(int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec& b) {
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = 1;
}

void vec2point(vec a, point& b) {
	b.x = ((float) a[0]) / a[2];
	b.y = ((float) a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec& c){
	c[0] = x; 
	c[1] = y; 
	c[2] = 1;
}

void unit(mat& a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat& c) {
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, float x, float y, mat& c) {
	unit(c);
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] =  cos(phi);

	c[0][M - 1] = -x * (cos(phi) - 1) + y * sin(phi);
	c[1][M - 1] = -y * (cos(phi) - 1) - x * sin(phi);
}

void scale(float Sx, float Sy, mat& c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
}

void reflect(bool xAxis, bool yAxis, mat& c) {
	unit(c);
	if (xAxis) {
		c[1][1] = -1;
	} 
	if (yAxis) {
		c[0][0] = -1;	
	}
}

void frame(float Vx, float Vy, float Vcx, float Vcy,
		   float Wx, float Wy, float Wcx, float Wcy,
		   mat& c) {

	unit(c);
	mat R, c1;

	move(-Vcx, -Vcy, R);
	times(R, c, c1);

	scale(Wx / Vx, Wy / Vy, R);
	times(R, c1, c);

	reflect(1, 0, R);
	times(R, c, c1);

	move(Wcx, Wcy, R);
	times(R, c1, c);
}

void times(mat3D a, mat3D b, mat3D &c) {
	unit(c);
	for(int i = 0; i < M3D; i++) {
		for(int j = 0; j < M3D; j++) {
			float skalaar = 0;
			for(int k = 0; k < M3D; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat3D a, vec3D b, vec3D &c) {
	for(int i = 0; i < M3D; i++) {
		float skalaar = 0;
		for(int j = 0; j < M3D; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat3D a, mat3D &b) {
	for(int i = 0; i < M3D; i++)
		for (int j = 0; j < M3D; j++)
			b[i][j] = a[i][j];
}

void sum(mat3D a, mat3D b, mat3D& c) {
	unit(c);
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void mult(mat3D a, float k, mat3D& c) {
	unit(c);
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			c[i][j] = a[i][j] * k;
		}
	}
}

void point2vec(point3D a, vec3D &b) {
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = a.z;
	b[3] = 1;
}

void vec2point(vec3D a, point3D &b) {
	b.x = ((float) a[0]) / a[3];
	b.y = ((float) a[1]) / a[3];
	b.z = ((float) a[2]) / a[3];
}

void makeHomogenVec(float x, float y, float z, vec3D &c) {
	c[0] = x; 
	c[1] = y; 
	c[2] = z;
	c[3] = 1;
}

void unit(mat3D &a) {
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, float Tz, mat3D &c) {
	unit(c);
	c[0][M3D - 1] = Tx;
	c[1][M3D - 1] = Ty;
	c[2][M3D - 1] = Tz;
}
void timesMatFloat (mat3D a, float b, mat3D &c) {
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			c[i][j] = a[i][j] * b;
		}
	}
}
void rotate (point3D n, float phi, mat3D &c) {
	unit(c);
	mat3D m1, m2, m3, t;

	unit(m1);
	unit(m2);
	unit(m3);

	m2[0][0] = 0;		m2[0][1] = -n.z;	m2[0][2] = n.y;	
	m2[1][0] = n.z;		m2[1][1] = 0;		m2[1][2] = -n.x;
	m2[2][0] = -n.y;	m2[2][1] = n.x;		m2[2][2] = 0;	

	mult(m2, sin(phi), t);
	sum(m1, t, m2);

	m3[0][0] = n.x * n.x - 1;	m3[0][1] = n.x * n.y;		m3[0][2] = n.x * n.z;
	m3[1][0] = n.x * n.y;		m3[1][1] = n.y * n.y - 1;	m3[1][2] = n.y * n.z;
	m3[2][0] = n.x * n.z;		m3[2][1] = n.y * n.z;		m3[2][2] = n.z * n.z - 1;

	float k = 1 - cos(phi);
	mult(m3, k, t);
	sum(m2, t, m3);

	m3[3][3] = 1;
	set(m3, c);
}

void scale(float Sx, float Sy, float Sz, mat3D &c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
	c[1][2] = Sz;
}

void sum(vec3D a, vec3D b, vec3D& c) {
	for (int i = 0; i < M3D - 1; i++) {
		c[i] = a[i] + b[i];
	}
	c[M3D - 1] = 1;
}

void sum(point3D a, point3D b, point3D& c) {
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

void mult(vec3D a, float k, vec3D& c) {
	for (int i = 0; i < M3D - 1; i++) {
		c[i] = a[i] * k;
	}
	c[M3D - 1] = 1;
}

void set(point3D a, point &b) {
	b.x = a.x;
	b.y = a.y;
}

void vecMult(vec3D a, vec3D b, vec3D& c) {
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	c[3] = 1;
}

void normalize(vec3D& v) {
	float len = vecLength(v);
	for (int i = 0; i < M3D - 1; i++) {
		v[i] = v[i] / len;
	}
	v[M3D - 1] = 1;
}

void sub(vec3D a, vec3D b, vec3D& c) {
	for (int i = 0; i < M3D - 1; i++) {
		c[i] = a[i] - b[i];
	}
	c[M3D - 1] = 1;
}

float vecLength(vec3D v) {
	float s = 0;
	for (int i = 0; i < M3D - 1; i++) {
		s += v[i] * v[i];
	}

	return sqrt(s);
}

void calculateAxes(point3D eye, point3D center, point3D up, vec3D& x, vec3D& y, vec3D& z) {
	vec3D s, p, u;

	point2vec(eye, s);
	point2vec(center, p);
	point2vec(up, u);

	normalize(u);

	vec3D es1, es2, es3, t1;

	mult(p, -1, t1);
	sum(s, t1, es3);
	normalize(es3);

	vecMult(u, es3, es1);
	normalize(es1);

	vecMult(es3, es1, es2);
	normalize(es2);

	x = es1;
	y = es2;
	z = es3;
}

void LookAt(point3D eye, point3D center, point3D up, mat3D &c) {
	unit(c);

	vec3D es1, es2, es3;

	calculateAxes(eye, center, up, es1, es2, es3);

	mat3D R1, R2;
	unit(R1);
	unit(R2);

	move(-eye.x, -eye.y, -eye.z, R1);

	R2[0][0] = es1[0];	R2[0][1] = es1[1];	R2[0][2] = es1[2];
	R2[1][0] = es2[0];	R2[1][1] = es2[1];	R2[1][2] = es2[2];
	R2[2][0] = es3[0];	R2[2][1] = es3[1];	R2[2][2] = es3[2];

	times(R2, R1, c);
}

void Ortho(float Vx, float Vy, float near, float far, mat3D &c) {
	unit(c);

	c[0][0] = 2.0 / Vx;
	c[1][1] = 2.0 / Vy;
	c[2][2] = 2.0 / (far - near);
	c[2][3] = (far + near) / (far - near);
}

void Perspective(float fovy, float aspect, float near, float far, mat3D &c) {
	unit(c);

	c[0][0] = (1.0 / aspect) * (1.0 / tan(fovy / 2.0));
	c[1][1] = 1.0 / tan(fovy / 2.0);
	c[2][2] = (far + near) / (far - near);
	c[2][3] = (2.0 * far * near) / (far - near);
	c[3][2] = -1.0;
	c[3][3] = 0;
}

float round(float x, int n) {
	int k = 1;
	for (int i = 0; i < n; i++) {
		k *= 10;
	}

	return ((float)((int)(x * k))) / k;
}