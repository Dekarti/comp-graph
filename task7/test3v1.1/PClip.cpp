#pragma once
#include "stdafx.h"
#include "Transform.h"

#define INFINITY float::MaxValue

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