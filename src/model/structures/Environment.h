//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_ENVIRONMENT_H
#define ARX_ENVIRONMENT_H

#include "utility/Vector.h"

class Environment {
    enum class Type { Tree, Rock };
    Vector3i position;
    Type type;

public:
    Environment();
    Environment(Type type, const Vector3i &position);
};


#endif //ARX_ENVIRONMENT_H
