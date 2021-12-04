//
// Created by Meevere on 27.11.2021.
//

#include "Container.h"

Container::Container()
: map(), objects(), size_z(0), size_x(0), size_y(0) {}

Container::Container(int _size_z, int _size_x, int _size_y)
: Container() {
    this->size_z = _size_z;
    this->size_x = _size_x;
    this->size_y = _size_y;
    
    map.resize(size_z);
    for( auto& sub_arr1 : map ){
        sub_arr1.resize(size_x);
        for( auto& sub_arr2 : sub_arr1 ){
            sub_arr2.reserve(size_y);
        }
    }

    // In case of map we also need to fill the map with proper Cells
    for (int i = 0; i < size_z; ++i) {
        for (int j = 0; j < size_x; ++j) {
            for (int k = 0; k < size_y; ++k) {
                map[i][j][k] = Cell{Vector3i{i,j,k}};
            }
        }
    }

    objects.resize(size_z);
    for( auto& sub_arr1 : objects ){
        sub_arr1.resize(size_x);
        for( auto& sub_arr2 : sub_arr1 ){
            sub_arr2.resize(size_y);
        }
    }


}


vector<vector<Cell>> &Container::getZSection(unsigned int z) { return map[z]; }


list<shared_ptr<Object>>& Container::get_at(int z, int x, int y) { return objects[z][x][y]; }
list<shared_ptr<Object>>& Container::get_at(const Vector3i &vec) { return get_at(vec[0], vec[1], vec[2]); }


void Container::add_at(int z, int x, int y, shared_ptr<Object>&& object) { objects[z][x][y].push_back(object); }
void Container::add_at(const Vector3i &vec, shared_ptr<Object>&& object) { add_at(vec[0], vec[1], vec[2], move(object)); }


bool Container::empty_at(int z, int x, int y) { return objects[z][x][y].empty();}
bool Container::empty_at(const Vector3i &vec) { return empty_at(vec[0], vec[1], vec[2]); }


Cell &Container::get_cell_at(int z, int x, int y){
    return map[z][x][y];
}
Cell &Container::get_cell_at(const Vector3i &vec) { return get_cell_at(vec[0], vec[1], vec[2]);}


// Const methods

const vector<vector<Cell>> &Container::getZSection(unsigned int z) const { return map[z]; }


const list<shared_ptr<Object>> &Container::get_at(int z, int x, int y) const { return objects[z][x][y]; }
const list<shared_ptr<Object>> &Container::get_at(const Vector3i &vec) const { return get_at(vec[0], vec[1], vec[2]); }


