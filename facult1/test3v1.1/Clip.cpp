#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Clip.h"

using namespace System::Drawing;

int calculateCode(point A, point Pmin, point Pmax) {
	int code = 0;
	if (A.x < Pmin.x) 
		code += 1;
	if (A.x > Pmax.x)
		code += 2;
	if (A.y < Pmin.y)
		code += 4;
	if (A.y > Pmax.y)
		code += 8;
	return code;
}


int isTrivialVisible(point A, point B, point Pmin, point Pmax) {
	int codeA = calculateCode(A, Pmin, Pmax);
	int codeB = calculateCode(B, Pmin, Pmax);
	if (!(codeA | codeB)) return 1;
	if (codeA && codeB) return 0;
	return -1;
}

void clip(point A, point B, point Pmin, point Pmax, Graphics^ g, Pen^ pen) {
	point mid;

	if ((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) <= 2) return;
	if (A.x == B.x && A.y == B.y) return;

	if (isTrivialVisible(A, B, Pmin, Pmax) == 1) {
		g->DrawLine(pen, A.x, A.y, B.x, B.y);
	} else if (isTrivialVisible(A, B, Pmin, Pmax) == 0) {
		return;
	} else if (isTrivialVisible(A, B, Pmin, Pmax) == -1) {
		mid.x = (A.x + B.x) / 2;
		mid.y = (A.y + B.y) / 2;
		clip(mid, B, Pmin, Pmax, g, pen);
		clip(A, mid, Pmin, Pmax, g, pen); 
	}
}

