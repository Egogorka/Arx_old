//
// Created by Meevere on 29.11.2021.
//

#include "Storehouse.h"

Storehouse::Storehouse(const Vector3i &position, int health, const Resource &resource)
: position(position), health(health), resource(resource) {}

Storehouse::Storehouse(const Vector3i &position)
: Storehouse(position, 100, Resource()){}

Storehouse::Storehouse()
: Storehouse(Vector3i{0,0,0}){}

std::string Storehouse::getObjectType() {
    return "storehouse";
}
