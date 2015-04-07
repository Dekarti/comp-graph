#include "Transform.h"
#include <map>
#include <vector>
#include <set>

polygon^ Pclip (polygon^ P, point Pmin, point Pmax);
void Pfill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C);
void PFill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C);
