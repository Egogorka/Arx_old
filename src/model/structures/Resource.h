//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_RESOURCE_H
#define ARX_RESOURCE_H

#include "utility/Vector.h"

class Resource {
    enum class Type { Wood, Stone, Fish };

    Vector3i position;
    Type type;
    int amount;

    Resource();
    Resource(Type type, int amount);
    Resource(Type type, int amount, const Vector3i& vec);
};


#endif //ARX_RESOURCE_H
