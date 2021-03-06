#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>


mat T;

void times(mat a, mat b, mat c) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			float skalaar = 0;
			for (int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;

		}
	}
}

void timesMatVec(mat a, vec b, vec c) {
	for (int i = 0; i < M; i++) {
		float skalaar = 0;
		for (int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat a, mat b) {
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec b) {
	b[0] = a.x; b[1] = a.y; b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = ((float)a[0]) / a[2];
	b.y = ((float)a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec c) {
	c[0] = x;
	c[1] = y;
	c[2] = 1;
}

void unit(mat a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat c) {
	unit (c);
	c[0][M-1] = Tx;
	c[1][M-1] = Ty;
}

void rotate(float phi, mat c) {
	unit (c);
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] = cos(phi);
}

void scale(float S, mat c) {
	unit (c);
	c[0][0] = S; c[1][1] = S;
}

// true  - relative to the x-axis
// false - relative to the y-axis
void mirror(bool axis, mat c) { 
	unit (c);
	(axis == true) ? c[1][1] = -1 : c[0][0] = -1; 
}

void rotateAbout(float phi, float x, float y, mat c) {
	unit(c);

	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] =  cos(phi);

	c[0][M - 1] = -x * (cos(phi) - 1) + y * sin(phi);
	c[1][M - 1] = -y * (cos(phi) - 1) - x * sin(phi);
}

void stretch(float Sx, float Sy, mat c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
}

void frame (float Vx, float Vy, float Vcx, float Vcy,
			float Wx, float Wy, float Wcx, float Wcy,
			mat c) {
	unit(c);
	mat R, T1;
	move(-Vcx, -Vcy, R);
	times(R, c, T1);
	set(T1, c);
	
	float xs = Wx / Vx;
	float ys = Wy / Vy;

	std::ofstream out("test.txt");
	out << "Vx = " << Vx << "\n"
		<< "Vy = " << Vy << "\n"
		<< "Vcx = " << Vcx << "\n"
		<< "Vcy = " << Vcy << "\n"
		<< "Wx = " << Wx << "\n"
		<< "Wy = " << Wy << "\n"
		<< "Wcx = " << Wcx << "\n"
		<< "Wcy = " << Wcy << "\n"
		<< "Wx / Vx = " << xs << "\n"
		<< "Wy / Vy = " << ys << "\n";

	stretch(xs, ys, R);
	times(R, c, T1);
	set(T1, c);

	mirror(true, R);
	times(R, c, T1);
	set(T1, c);

	move(Wcx, Wcy, R);
	times(R, c, T1);
	set(T1, c);
}

