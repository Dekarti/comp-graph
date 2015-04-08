#pragma once
#include "stdafx.h"
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include "Transform.h"

#define INFINITY float::MaxValue

using namespace std;
using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Drawing;

polygon^ Pclip (polygon^ P, point Pmin, point Pmax) {
	polygon^ P1 = gcnew polygon(0);
	point A = P[P->Count - 1];
	int k = 0;
	while (k < P->Count) {
		point B = P[k];
		float t1out, t2in, t2out,
			  xin, xout, txin, txout,
			  yin, yout, tyin, tyout;
		float dx = B.x - A.x;
		float dy = B.y - A.y;
		if (dx > 0 || dx == 0 && A.x > Pmax.x) {
			xin  = Pmin.x;
			xout = Pmax.x;
		}
		else {
			xin  = Pmax.x;
			xout = Pmin.x;
		}
		if (dy > 0 || dy == 0 && A.y > Pmax.y) {
			yin  = Pmin.y;
			yout = Pmax.y;
		}
		else {
			yin  = Pmax.y;
			yout = Pmin.y;
		}

		if (dx != 0)
			txout = (xout - A.x) / dx;
		else if (A.x >= Pmin.x && A.x <= Pmax.x)
			txout = INFINITY;
		else 
			txout = -INFINITY;

		if (dy != 0)
			tyout = (yout - A.y) / dy;
		else if (A.y >= Pmin.y && A.y <= Pmax.y)
			tyout = INFINITY;
		else 
			tyout = -INFINITY;

		if (txout < tyout) {
			t1out = txout;
			t2out = tyout;
		}
		else {
			t1out = tyout;
			t2out = txout;
		}

		if (t2out > 0) {
			if (dx != 0)
				txin = (xin - A.x) / dx;
			else
				txin = -INFINITY;
			
			if (dy != 0)
				tyin = (yin - A.y) / dy;
			else
				tyin = -INFINITY;

			if (txin < tyin)
				t2in = tyin;
			else
				t2in = txin;

			if (t1out < t2in) {
				if (t1out > 0 && t1out <= 1) {
					if (txin < tyin) {
						P1->Add(point(xout, yin));
					}
					else {
						P1->Add(point(xin, yout));
					}	
				}
			}
			else if (t1out > 0 && t2in <=1) {
				if (t2in >= 0) { 
					if (txin > tyin) {
						P1->Add(point(xin, A.y + txin * dy));
					}
					else {
						P1->Add(point(A.x + tyin * dx, yin));
					}
				}
				if (t1out <= 1) {
					if (txout < tyout) {
						P1->Add(point(xout, A.y + txout * dy));
					}
					else {
						P1->Add(point(A.x + tyout * dx, yout));
					}
				}
				else {
					P1->Add(B);
				}
			}

			if (t2out > 0 && t2out <= 1) {
				P1->Add(point(xout, yout));
			}
		}
		k++;
		A = B;
	}
	return P1;
}


int compareByStartY(line l1, line l2) {
	return (int)l1.start.y - l2.start.y;
}

void PFill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C) {

	Graphics^ g = Graphics::FromImage(image);
	Pen^ pen = gcnew Pen(C);
	List<line> S;
	List<ternary^> AEL;

	point A = P[P->Count - 1];
	int k = 0;
	while (k < P->Count) {
		point B = P[k];
		if (A.y <= B.y) {
			line l = {A, B};
			S.Add(l);
		}
		else {
			line l = {B, A};
			S.Add(l);
		}
		k++;
		A = B;
	}

	S.Sort(gcnew Comparison<line>(compareByStartY));

	float ymin = S[0].start.y;

	float ymax = ymin;
	for (int i = 0; i < P->Count; i++) {
		if (P[i].y > ymax)
			ymax = P[i].y;
	}

	int yt = ymin;
	while (yt <= ymax) {
		for (int i = 0; i < S.Count; i++) {
			if ((int)S[i].start.y == yt &&
				(int)S[i].start.y != (int)S[i].end.y) {
				float dx = (S[i].end.x - S[i].start.x) / (float)(S[i].end.y - S[i].start.y);
				ternary^ t = { S[i].start.x, S[i].end.y, dx };
				AEL.Add(t);
			}
			if (S[i].start.y == yt &&
				(int)S[i].start.y == (int)S[i].end.y) {
				g->DrawLine(pen, S[i].start.x, (float)yt, S[i].end.x, (float)yt);
			}
			if ((int)S[i].start.y == yt) {
					S.RemoveAt(i);
					i--;
			}

		}
		if (!AEL.Count) return;
		
		for (int i = AEL.Count - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (AEL[j][0] - AEL[j + 1][0] > 0) {
					ternary^ t = AEL[i];
					AEL[i] = AEL[j];
					AEL[j] = t;
				}
				if (AEL[j][0] == AEL[j + 1][0] && AEL[j][2] > AEL[j + 1][2]) {
					ternary^ t = AEL[i];
					AEL[i] = AEL[j];
					AEL[j] = t;
				}
			}
		}

		int yNext = AEL[0][1];
		for (int i = 0; i < AEL.Count; i++)
			if (yNext > (int)AEL[i][1])
				yNext = AEL[i][1];
		if (S.Count)
			yNext = std::min((int)S[0].start.y, yNext);

		while (yt < yNext) {
			for (int i = 0; i < AEL.Count; i += 2) {
				g->DrawLine(pen, AEL[i][0], (float)yt, AEL[i+1][0], (float)yt);
				AEL[i][0] += AEL[i][2];
				AEL[i+1][0] += AEL[i+1][2];
			}
			yt++;
		}

		for (int i = AEL.Count - 1; i >= 0; i--) {
			if ((int)AEL[i][1] <= yt) {
				AEL.RemoveAt(i);
			}
		}
	}
}