//
// Created by Meevere on 27.11.2021.
//

#include "Container.h"

Container::Container():map(), objects() {}

Container::Container(int size_z, int size_x, int size_y): Container() {
    map.resize(size_z);
    for( auto& sub_arr1 : map ){
        sub_arr1.resize(size_x);
        for( auto& sub_arr2 : map ){
            sub_arr2.reserve(size_y);
        }
    }
}


std::vector<std::vector<Cell>> &Container::getZSection(unsigned int z) { return map[z]; }

std::list<std::shared_ptr<Object>> &Container::get_at(int z, int x, int y) { return objects[z][x][y]; }
std::list<std::shared_ptr<Object>> &Container::get_at(const Vector3i &vec) { return get_at(vec[0], vec[1], vec[2]); }

void Container::add_at(int z, int x, int y, std::shared_ptr<Object> &object) { objects[z][x][y].push_back(object); }
void Container::add_at(const Vector3i &vec, std::shared_ptr<Object>& object) { add_at(vec[0], vec[1], vec[2], object); }


// Const methods

const std::vector<std::vector<Cell>> &Container::getZSection(unsigned int z) const { return map[z]; }

const std::list<std::shared_ptr<Object>> &Container::get_at(int z, int x, int y) const { return objects[z][x][y]; }
const std::list<std::shared_ptr<Object>> &Container::get_at(const Vector3i &vec) const { return get_at(vec[0], vec[1], vec[2]); }
