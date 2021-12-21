//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_ENVIRONMENT_H
#define ARX_ENVIRONMENT_H

#include "utility/Vector.h"
#include "src/model/Object.h"

struct Environment : public Object {
    enum class Type { Tree, Rock };

    Type type;

    Environment();
    Environment(Type type, const Vector3i &position);

    std::string getObjectType() override;
};


#endif //ARX_ENVIRONMENT_H
