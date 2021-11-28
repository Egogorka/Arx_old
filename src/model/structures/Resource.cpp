//
// Created by Meevere on 29.11.2021.
//

#include "Resource.h"

Resource::Resource(Resource::Type type, int amount, const Vector3i& vec): type(type), amount(amount), position(vec) {}
Resource::Resource(Resource::Type type, int amount): Resource(type, amount, Vector3i{0,0,0}) {}
Resource::Resource(): Resource(Type::Wood, 0) {}
