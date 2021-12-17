//
// Created by ACER on 17.12.2021.
//

#ifndef ARX_PATHTO_H
#define ARX_PATHTO_H

#include "utility/Vector.h"
#include <list>
#include <vector>

using namespace  std;

list <Vector2i> PathTo (Vector2i in, Vector2i out, vector<vector<int>>& array_out);
int Test();

#endif //ARX_PATHTO_H
