#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Clip.h"

#define ARGS_DEF	point &A, point &B, point Pmin, point Pmax
#define ARGS		A, B, Pmin, Pmax

void clip1Left	(ARGS_DEF) {
	A.y = B.y - (B.x - Pmin.x) * (B.y - A.y) / (B.x - A.x);
	A.x = Pmin.x;
}
void clip1Top	(ARGS_DEF) {
	A.x = B.x - (B.y - Pmax.y) * (B.x - A.x) / (B.y - A.y);
	A.y = Pmax.y;
}
void clip1Bottom(ARGS_DEF) {
	A.x = B.x - (B.y - Pmin.y) * (B.x - A.x) / (B.y - A.y);
	A.y = Pmin.y;
}
void clip2Right	(ARGS_DEF) {
	B.y = A.y + (Pmax.x - A.x) * (B.y - A.y) / (B.x - A.x);
	B.x = Pmax.x;
}
void clip2Top	(ARGS_DEF) {
	B.x = A.x + (Pmax.y - A.y) * (B.x - A.x) / (B.y - A.y);
	B.y = Pmax.y;
}
void clip2Bottom(ARGS_DEF) {
	B.x = A.x + (Pmin.y - A.y) * (B.x - A.x) / (B.y - A.y);
	B.y = Pmin.y;
}


bool clip(ARGS_DEF) {
	std::ofstream out("test3.txt");
	// 1 
	if (A.x > B.x) 
		std::swap(A, B);

	// 2
	int C1 = 0;
	int C2 = 0;

	if (A.x < Pmin.x) 
		C1 += 1;
	if (A.x > Pmax.x)
		C1 += 2;
	if (A.y < Pmin.y)
		C1 += 4;
	if (A.y > Pmax.y)
		C1 += 8;

	if (B.x < Pmin.x) 
		C2 += 1;
	if (B.x > Pmax.x)
		C2 += 2;
	if (B.y < Pmin.y)
		C2 += 4;
	if (B.y > Pmax.y)
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
			if (B.y < Pmin.y)
				clip2Bottom(ARGS);
			return true;
		case 0x08 :
			clip2Top(ARGS);
			return true;
		case 0x0A :
			clip2Right(ARGS);
			if (B.y > Pmax.y)
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
			if (A.y < Pmin.y) 
				return false;
			clip2Bottom(ARGS);
			return true;
		case 0x16 :
			clip1Left(ARGS);
			if (A.y < Pmin.y)
				return false;
			clip2Bottom(ARGS);
			if (B.x > Pmax.x)
				clip2Right(ARGS);
			return true;
		case 0x18 :
			clip1Left(ARGS);
			if (A.y > Pmax.y)
				return false;
			clip2Top(ARGS);
			return true;
		case 0x1A :
			clip1Left(ARGS);
			if (A.y > Pmax.y)
				return false;
			clip2Top(ARGS);
			if (B.x > Pmax.x)
				clip2Right(ARGS);
			return true;
		case 0x40 :
			clip1Bottom(ARGS);
			return true;
		case 0x42 :
			clip1Bottom(ARGS);
			if (A.x > Pmax.x)
				return false;
			clip2Right(ARGS);
			return true;
		case 0x48 :
			clip1Bottom(ARGS);
			clip2Top(ARGS);
			return true;
		case 0x4A :
			clip1Bottom(ARGS);
			if (A.x > Pmax.x) 
				return false;
			clip2Right(ARGS);
			if (B.y > Pmax.y)
				clip2Top(ARGS);
			return true;
		case 0x50 :
			clip1Left(ARGS);
			if (A.y < Pmin.y)
				clip1Bottom(ARGS);
			return true;
		case 0x52 :
			clip1Bottom(ARGS);
			if (A.x  > Pmax.x) 
				return false;
			if (A.x < Pmin.x)
				clip1Left(ARGS);
			clip2Right(ARGS);
			return true;
		case 0x58 :
			clip1Left(ARGS);
			if (A.y > Pmax.y) 
				return false;
			if (A.y < Pmin.y)
				clip1Bottom(ARGS);
			clip2Top(ARGS);
			return true;
		case 0x5A :
			clip1Left(ARGS);
			if (A.y > Pmax.y) 
				return false;
			if (A.y < Pmin.y) {
				clip1Bottom(ARGS);
				if (A.x > Pmax.x)
					return false;
			}
			clip2Top(ARGS);
			if (B.x > Pmax.x)
				clip2Right(ARGS);
			return true;
		case 0x80 :
			clip1Top(ARGS);
			return true;
		case 0x82 :
			clip1Top(ARGS);
			if (A.x > Pmax.x) 
				return false;
			clip2Right(ARGS);
			return true;
		case 0x84 :
			clip1Top(ARGS);
			clip2Bottom(ARGS);
			return true;
		case 0x86 :
			clip1Top(ARGS);
			if (A.x > Pmax.x) 
				return false;
			clip2Right(ARGS);
			if (B.y < Pmin.y)
				clip2Bottom(ARGS);
			return true;
		case 0x90 :
			clip1Left(ARGS);
			if (A.y > Pmax.y)
				clip1Top(ARGS);
			return true;
		case 0x92 :
			clip1Top(ARGS);
			if (A.x > Pmax.x) 
				return false;
			if (A.x < Pmin.x)
				clip1Left(ARGS);
			clip2Right(ARGS);
			return true;
		case 0x94 :
			clip1Left(ARGS);
			if (A.y < Pmin.y) 
				return false;
			if (A.y > Pmax.y)
				clip1Top(ARGS);
			clip2Bottom(ARGS);
			return true;
		case 0x96 :
			clip1Left(ARGS);
			if (A.y < Pmin.y) 
				return false;
			if (A.y > Pmax.y) {
				clip1Top(ARGS);
				if (A.x > Pmax.x) 
					return false;
			}
			clip2Bottom(ARGS);
			if (B.x > Pmax.x)
				clip2Right(ARGS);	
			return true;
	}
	return false;

}
