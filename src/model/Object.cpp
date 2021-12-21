//
// Created by Meevere on 27.11.2021.
//

#include "Object.h"

std::string Object::getObjectType() {
    return "object";
}

void Object::update() {}

Object::Object(const Vector3i &position) : position(position) {}