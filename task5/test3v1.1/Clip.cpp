#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Clip.h"

#define ARGS_DEF	float x1, float y1, float x2, float y2, point Pmin, point Pmax
#define ARGS		x1, y1, x2, y2, Pmin, Pmax

void clip1Left	(ARGS_DEF) {
	y1 = y2 - (x2 - Pmin.x) * (y2 - y1) / (x2 - x1);
	x1 = Pmin.x;
}
void clip1Top	(ARGS_DEF) {
	x1 = x2 - (y2 - Pmax.y) * (x2 - x1) / (y2 - y1);
	y1 = Pmax.y;
}
void clip1Bottom(ARGS_DEF) {
	x1 = x2 - (y2 - Pmin.y) * (x2 - x1) / (y2 - y1);
	y1 = Pmin.y;
}
void clip2Right	(ARGS_DEF) {
	y2 = y1 + (Pmax.x - x1) * (y2 - y1) / (x2 - x1);
	x2 = Pmax.x;
}
void clip2Top	(ARGS_DEF) {
	x2 = x1 + (Pmax.y - y1) * (x2 - x1) / (y2 - y1);
	y2 = Pmax.y;
}
void clip2Bottom(ARGS_DEF) {
	x2 = x1 + (Pmin.y - y1) * (x2 - x1) / (y2 - y1);
	y2 = Pmin.y;
}


bool clip(ARGS_DEF) {
	std::ofstream out("test3.txt");
	// 1 
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	// 2
	int C1 = 0;
	int C2 = 0;

	if (x1 < Pmin.x) 
		C1 += 1;
	if (x1 > Pmax.x)
		C1 += 2;
	if (y1 < Pmin.y)
		C1 += 4;
	if (y1 > Pmax.y)
		C1 += 8;

	if (x2 < Pmin.x) 
		C2 += 1;
	if (x2 > Pmax.x)
		C2 += 2;
	if (y2 < Pmin.y)
		C2 += 4;
	if (y2 > Pmax.y)
		C2 += 8;

	// 3
	if (C1 & C2) 
		return false;

	// 4
	int C = C1 * 16 + C2;

	// 5 .. 32
	switch (C) {
		case 0x00 :
			return true;
		case 0x02 :
			clip2Right(ARGS);
			return true;
		case 0x04 :
			clip2Bottom(ARGS);
			return true;
		case 0x06 :
			clip2Right(ARGS);
			if (y2 < Pmin.y)
				clip2Bottom(ARGS);
			return true;
		case 0x08 :
			clip2Top(ARGS);
			return true;
		case 0x0A :
			clip2Right(ARGS);
			if (y2 > Pmax.y)
				clip2Top(ARGS);
			return true;
		case 0x10 :
			clip1Left(ARGS);
			return true;
		case 0x12 :
			clip1Left(ARGS);
			clip2Right(ARGS);
			return true;
		case 0x14 :
			clip1Left(ARGS);
			if (y1 < Pmin.y) 
				return false;
			clip2Bottom(ARGS);
			return true;
		case 0x16 :
			clip1Left(ARGS);
			if (y1 < Pmin.y)
				return false;
			clip2Bottom(ARGS);
			if (x2 > Pmax.x)
				clip2Right(ARGS);
			return true;
		case 0x18 :
			clip1Left(ARGS);
			if (y1 > Pmax.y)
				return false;
			clip2Top(ARGS);
			return true;
		case 0x1A :
			clip1Left(ARGS);
			if (y1 > Pmax.y)
				return false;
			clip2Top(ARGS);
			if (x2 > Pmax.x)
				clip2Right(ARGS);
			return true;
		case 0x40 :
			clip1Bottom(ARGS);
			return true;
		case 0x42 :
			clip1Bottom(ARGS);
			if (x1 > Pmax.x)
				return false;
			clip2Right(ARGS);
			return true;
		case 0x48 :
			clip1Bottom(ARGS);
			clip2Top(ARGS);
			return true;
		case 0x4A :
			clip1Bottom(ARGS);
			if (x1 > Pmax.x) 
				return false;
			clip2Right(ARGS);
			if (y2 > Pmax.y)
				clip2Top(ARGS);
			return true;
		case 0x50 :
			clip1Left(ARGS);
			if (y1 < Pmin.y)
				clip1Bottom(ARGS);
			return true;
		case 0x52 :
			clip1Bottom(ARGS);
			if (x1  > Pmax.x) 
				return false;
			if (x1 < Pmin.x)
				clip1Left(ARGS);
			clip2Right(ARGS);
			return true;
		case 0x58 :
			clip1Left(ARGS);
			if (y1 > Pmax.y) 
				return false;
			if (y1 < Pmin.y)
				clip1Bottom(ARGS);
			clip2Top(ARGS);
			return true;
		case 0x5A :
			clip1Left(ARGS);
			if (y1 > Pmax.y) 
				return false;
			if (y1 < Pmin.y) {
				clip1Bottom(ARGS);
				if (x1 > Pmax.x)
					return false;
			}
			clip2Top(ARGS);
			if (x2 > Pmax.x)
				clip2Right(ARGS);
			return true;
		case 0x80 :
			clip1Top(ARGS);
			return true;
		case 0x82 :
			clip1Top(ARGS);
			if (x1 > Pmax.x) 
				return false;
			clip2Right(ARGS);
			return true;
		case 0x84 :
			clip1Top(ARGS);
			clip2Bottom(ARGS);
			return true;
		case 0x86 :
			clip1Top(ARGS);
			if (x1 > Pmax.x) 
				return false;
			clip2Right(ARGS);
			if (y2 < Pmin.y)
				clip2Bottom(ARGS);
			return true;
		case 0x90 :
			clip1Left(ARGS);
			if (y1 > Pmax.y)
				clip1Top(ARGS);
			return true;
		case 0x92 :
			clip1Top(ARGS);
			if (x1 > Pmax.x) 
				return false;
			if (x1 < Pmin.x)
				clip1Left(ARGS);
			clip2Right(ARGS);
			return true;
		case 0x94 :
			clip1Left(ARGS);
			if (y1 < Pmin.y) 
				return false;
			if (y1 > Pmax.y)
				clip1Top(ARGS);
			clip2Bottom(ARGS);
			return true;
		case 0x96 :
			clip1Left(ARGS);
			if (y1 < Pmin.y) 
				return false;
			if (y1 > Pmax.y) {
				clip1Top(ARGS);
				if (x1 > Pmax.x) 
					return false;
			}
			clip2Bottom(ARGS);
			if (x2 > Pmax.x)
				clip2Right(ARGS);	
			return true;
	}
	return false;

}
