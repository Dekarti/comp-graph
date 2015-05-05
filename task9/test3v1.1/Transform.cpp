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
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			float skalaar = 0;
			for(int k = 0; k < N; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat3D a, vec3D b, vec3D &c) {
	for(int i = 0; i < N; i++) {
		float skalaar = 0;
		for(int j = 0; j < N; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat3D a, mat3D &b) {
	for(int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			b[i][j] = a[i][j];
}

void sum(mat3D a, mat3D b, mat3D& c) {
	unit(c);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void mult(mat3D a, float k, mat3D& c) {
	unit(c);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
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
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, float Tz, mat3D &c) {
	unit(c);
	c[0][N - 1] = Tx;
	c[1][N - 1] = Ty;
	c[2][N - 1] = Tz;
}
void timesMatFloat (mat3D a, float b, mat3D &c) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			c[i][j] = a[i][j] * b;
		}
	}
}
void rotate (point3D n, float phi, mat3D &c) {
	float n1 = n.x;
	float n2 = n.y;
	float n3 = n.z;

	c[0][0] = n1 * n1 + (1 - n1 * n1) * cos(phi);
	c[0][1] = n1 * n2 * (1 - cos(phi)) - n3 * sin(phi);
	c[0][2] = n1 * n3 * (1 - cos(phi)) + n2 * sin(phi);

	c[1][0] = n1 * n2 * (1 - cos(phi)) + n3 * sin(phi);
	c[1][1] = n2 * n2 + (1 - n2 * n2) * cos(phi);
	c[1][2] = n2 * n3 * (1 - cos(phi)) - n1 * sin(phi);

	c[2][0] = n1 * n3 * (1 - cos(phi)) - n2 * sin(phi);
	c[2][1] = n2 * n3 * (1 - cos(phi)) + n1 * sin(phi);
	c[2][2] = n3 * n3 + (1 - n3 * n3) * cos(phi);
}

void scale(float Sx, float Sy, float Sz, mat3D &c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
	c[1][2] = Sz;
}

vec3D operator+ (vec3D a, vec3D b) {
	vec3D c;
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
	c[3] = 1;
	return c;
}

point3D operator+ (point3D a, point3D b) {
	point3D c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

vec3D   operator- (vec3D a, vec3D b) {
	vec3D c;
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
	c[3] = 1;
	return c;
}

vec3D operator* (vec3D a, float k) {
	vec3D c;
	c[0] = a[0] * k;
	c[1] = a[1] * k;
	c[2] = a[2] * k;
	c[3] = 1;
	return c;
}

void set(point3D a, point &b) {
	b.x = a.x;
	b.y = a.y;
}

void crossProduct(vec3D a, vec3D b, vec3D& c) {
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	c[3] = 1;
}

float lengthVec(vec3D a) {
	return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}


void normalize(vec3D& a) {
	float length = lengthVec(a);
	a[0] = a[0] / length;
	a[1] = a[1] / length;
	a[2] = a[2] / length;
	a[3] = 1;
}

void LookAt(point3D eye, point3D center, point3D up, mat3D &c) {
	unit(c);
	mat3D R1, R2;
	unit(R2);

	move(-eye.x, -eye.y, -eye.z, R1);

	vec3D e1, e2, e3;
	vec3D s, p, u;

	point2vec(eye, s);
	point2vec(center, p);
	point2vec(up, u);

	normalize(u);
	e3 = s - p;
	normalize(e3);

	crossProduct(u, e3, e1);
	normalize(e1);

	crossProduct(e3, e1, e2);
	normalize(e2);

	R2[0][0] = e1[0];	R2[0][1] = e1[1];	R2[0][2] = e1[2];
	R2[1][0] = e2[0];	R2[1][1] = e2[1];	R2[1][2] = e2[2];
	R2[2][0] = e3[0];	R2[2][1] = e3[1];	R2[2][2] = e3[2];

	times(R2, R1, c);
}

void Ortho(float Vx, float Vy, float near, float far, mat3D &c) {
	unit(c);
	
	c[0][0] = 2.0 / Vx;
	c[1][1] = 2.0 / Vy;
	c[2][2] = 2.0 / (far - near);
	c[2][3] = (far + near) / (far - near);
}

void Frustrum (float Vx, float Vy, float near, float far, mat3D &c) {
	unit(c);
	c[0][0] = near * 2 / Vx;
	c[1][1] = near * 2 / Vy;
	c[2][2] = (far + near) / (far - near);
	c[3][3] = 0;
	c[3][2] = -1;
	c[2][3] = 2 * far * near / (far - near);
}

void Perspective (float fovy, float aspect, float near, float far, mat3D &c) {
	float Vy = 2 * near * tan(fovy / 2);
	float Vx = aspect * Vy;
	Frustrum(Vx, Vy, near, far, c);
}