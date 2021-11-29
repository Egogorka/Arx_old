//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_STOREHOUSE_H
#define ARX_STOREHOUSE_H

#include "src/model/Object.h"
#include "src/model/structures/Resource.h"

#include "utility/Vector.h"

struct Storehouse : public Object {
    Resource resource;
    int health;
    Vector3i position;

    Storehouse();
    explicit Storehouse(const Vector3i& position);
    Storehouse(const Vector3i& position, int health, const Resource& resource);

    std::string getObjectType() override;
};


#endif //ARX_STOREHOUSE_H
