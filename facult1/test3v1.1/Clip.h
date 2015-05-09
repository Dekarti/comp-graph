#pragma once
#include "stdafx.h"
#include "Transform.h"

using namespace System::Drawing;

//bool clip(point a, point b, point Pmin, point Pmax, point &A, point &B);
void clip(point A, point B, point Pmin, point Pmax, Graphics^ g, Pen^ pen);


