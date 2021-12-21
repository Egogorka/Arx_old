//
// Created by Meevere on 29.11.2021.
//

#include "Environment.h"

Environment::Environment(Environment::Type type, const Vector3i &position):
    Object(position),
    type(type) {}

Environment::Environment():
    Environment(Type::Rock, Vector3i{0,0,0}) {}

std::string Environment::getObjectType() {
    return "environment";
}
