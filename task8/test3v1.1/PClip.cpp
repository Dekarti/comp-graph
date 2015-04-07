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
using namespace System::Collections;
using namespace System::Collections::Generic;

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

/*void Pfill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C) {

	Generic::List<line> S;
	Generic::List<ternary> AEL;
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
	
	for(int i = 0; i < S.Count; i++)
		for(int j = i + 1; j < S.Count; j++)
			if(S[j].start.y < S[i].start.y)
				swap(S[i], S[j]);

	float ymin = S[0].start.y;
	float ymax = S[S.Count - 1].end.y;

	float yt = ymin;
	float ysnext = ymin;
	float yAELnext;
	while (yt <= ymax) {
		if (yt == ysnext) {
			for (int i = 0; i < S.Count; i++) {
				if (S[i].start.y == yt && S[i].start.y != S[i].end.y) {
					float dx = (S[i].end.x - S[i].start.x) / (S[i].end.y - S[i].start.y);
					ternary t = { S[i].start.x, S[i].end.y, dx };
					AEL.Add(t);
				}
				if (S[i].start.y == yt && S[i].start.y == S[i].end.y) {
					for (int x = S[i].start.x; x <= S[i].end.x; x++)
						image->SetPixel(x, yt, C);
				}
			}
			if(!AEL.Count) return;

			for (int i = S.Count - 1; i >=0; i--) {
				if (S[i].start.y == yt) {
					S.RemoveAt(i);
				}
			}

			for (int i = 0; i < S.Count; i++) {
				if (S[i].start.y <= ysnext)
					ysnext = S[i].start.y;
			}

			for (int i = 0; i < AEL.Count; i++) {
				for (int j = i + 1; j < AEL.Count; j++) {
					if (AEL[j].x1 < AEL[i].x1)
						swap(AEL[i], AEL[j]);
					else if (AEL[j].x1 == AEL[i].x1)
						if (AEL[j].dx < AEL[i].dx)
							swap(AEL[i], AEL[j]);
				}
			}
			
			yAELnext = AEL[0].y2;
			for (int i = 0; i < AEL.Count; i++) {
				if (AEL[i].y2 != yt && AEL[i].y2 <= yAELnext)
					yAELnext = AEL[i].y2;
			}
		}

		for (int i = 0; i < AEL.Count - 1; i += 2) {
			for (int x = AEL[i].x1; x <= AEL[i + 1].x1; x++)
				image->SetPixel(x, yt, C);
		}

		for (int i = 0; i < AEL.Count; i++) {
			AEL[i].x1 = AEL[i].x1 * AEL[i].dx;
		}

		yt++;

		if (yt >= yAELnext) {
			for (int i = AEL.Count - 1; i >=0; i--) {
				if (AEL[i].y2 <= yt) {
					AEL.RemoveAt(i);
				}
			}

			for (int i = 0; i < AEL.Count; i++) {
				if (AEL[i].y2 != yt && AEL[i].y2 <= yAELnext)
					yAELnext = AEL[i].y2;
			}
		}
	}

}*/

void PFill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C) {
	List<line> S;
	List<ternary> AEL;

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
	
	for(int i = 0; i < S.Count; i++)
		for(int j = i + 1; j < S.Count; j++)
			if(S[j].start.y < S[i].start.y)
				swap(S[i], S[j]);

	float ymin = S[0].start.y;

	float ymax = ymin;
	for (int i = 0; i < P->Count; i++) {
		if (P[i].y > ymax)
			ymax = P[i].y;
	}

	float yt = ymin;
	while (yt <= ymax) {
		for (int i = 0; i < S.Count; i++) {
			if (S[i].start.y == yt && S[i].start.y != S[i].end.y) {
				float dx = (float)(S[i].end.x - S[i].start.x) / (float)(S[i].end.y - S[i].start.y);
				ternary t = { S[i].start.x, S[i].end.y, dx };
				AEL.Add(t);
			}
			if (S[i].start.y == yt && S[i].start.y == S[i].end.y) {
				for (int x = S[i].start.x; x <= S[i].end.x; x++)
					image->SetPixel(x, yt, System::Drawing::Color::Blue);
			}
		}
		if (!AEL.Count) return;
		float yNext = int::MaxValue;
		for (int i = 0; i < AEL.Count; i++) {
			if (yNext != yt && yNext > AEL[i].y2)
				yNext = AEL[i].y2;
		}
		
		for (int i = 0; i < AEL.Count; i++) {
			for (int j = i + 1; j < AEL.Count; j++) {
				if (AEL[j].x1 < AEL[i].x1)
					swap(AEL[i], AEL[j]);
			}
		}

		for (int i = 0; i < AEL.Count; i++) {
			for (int j = i + 1; j < AEL.Count; j++) {
				if (AEL[j].x1 == AEL[i].x1 && AEL[j].dx < AEL[i].dx)
					swap(AEL[i], AEL[j]);
			}
		}

		while (yt < yNext) {
			for (int i = 0; i < AEL.Count - 1; i += 2) {
				for (float x = AEL[i].x1; x <= AEL[i + 1].x1; x += 1.0) {
					image->SetPixel(x, yt, System::Drawing::Color::Blue);
					
				}
				AEL[i].x1 = AEL[i].x1 + AEL[i].dx;
				AEL[i + 1].x1 = AEL[i + 1].x1 + AEL[i + 1].dx;
			}
			yt++;
		}

		for (int i = AEL.Count - 1; i >= 0; i--) {
			if (AEL[i].y2 <= yt) {
				AEL.RemoveAt(i);
			}
		}
	}
}