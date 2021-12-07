//
// Created by Meevere on 27.11.2021.
//

#include "Container.h"


ContainerUnit::ContainerUnit(const Cell &cell, const Vector3i &pos) : cell(cell), pos(pos), objects() {}
ContainerUnit::ContainerUnit(const Cell &cell) : ContainerUnit(cell, Vector3i{0,0,0}) {}
ContainerUnit::ContainerUnit(): ContainerUnit(Cell()) {}

void ContainerUnit::add(shared_ptr<Object> &&object) {
    objects.push_back(object);
}

Container::Container()
: map(), size_z(0), size_x(0), size_y(0) {}

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
                Vector3i pos{i,j,k};
                map[i][j].emplace_back(Cell{pos},pos);
            }
        }
    }
}


list<shared_ptr<Object>>& Container::get_at(int z, int x, int y) { return map[z][x][y].objects; }
list<shared_ptr<Object>>& Container::get_at(const Vector3i &vec) { return get_at(vec[0], vec[1], vec[2]); }

ContainerUnit &Container::get(int z, int x, int y) { return map[z][x][y]; }
ContainerUnit &Container::get(const Vector3i &vec) { return get(vec.z(), vec.x(), vec.y());}

void Container::add_at(int z, int x, int y, shared_ptr<Object>&& object) { map[z][x][y].add(move(object)); }
void Container::add_at(const Vector3i &vec, shared_ptr<Object>&& object) { add_at(vec[0], vec[1], vec[2], move(object)); }


bool Container::empty_at(int z, int x, int y) { return map[z][x][y].objects.empty();}
bool Container::empty_at(const Vector3i &vec) { return empty_at(vec[0], vec[1], vec[2]); }


Cell &Container::get_cell_at(int z, int x, int y){
    return map[z][x][y].cell;
}
Cell &Container::get_cell_at(const Vector3i &vec) { return get_cell_at(vec[0], vec[1], vec[2]);}


// Const methods


const list<shared_ptr<Object>> &Container::get_at(int z, int x, int y) const { return map[z][x][y].objects; }
const list<shared_ptr<Object>> &Container::get_at(const Vector3i &vec) const { return get_at(vec[0], vec[1], vec[2]); }

/////////////////////////////////////////////////////////////////////////////////////////////
// Iterator support
/////////////////////////////////////////////////////////////////////////////////////////////
// Constructors


Container::Iterator::Iterator(const Vector3i &pos, Container &container)
: pos(pos), container(&container) {}


Container::Iterator::Iterator(const Container::Iterator &it)
: pos(it.pos), container(it.container) {}


Container::Iterator &Container::Iterator::operator=(const Container::Iterator &it) = default;


Container::Iterator::Iterator(Vector3i &&pos, Container &container): Container::Iterator(pos, container) {}


/////////////////////////////////////////////////////////////////////////////////////////////
// Methods


Container::Iterator Container::Iterator::operator++() {
    if(++pos.x() < container->size_x) return *this;
    pos.x() = 0;
    if(++pos.y() < container->size_y) return *this;
    pos.y() = 0;
    if(++pos.z() < container->size_z) return *this;
    // If we pass each if-statement - then we are at the end of container
    *this = container->end();
    return *this;
}


Container::Iterator::pointer Container::Iterator::operator->() { return &container->get(pos); }

const Container::Iterator Container::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

Container::Iterator::reference Container::Iterator::operator*() {
    return container->get(pos);
}

bool operator==(const Container::Iterator &a, const Container::Iterator &b) { return a.pos == b.pos; }
bool operator!=(const Container::Iterator &a, const Container::Iterator &b) { return a.pos != b.pos; }


Container::Iterator Container::begin() {
    return Container::Iterator(Vector3i{0,0,0}, *this);
}

Container::Iterator Container::end() {
    return Container::Iterator(Vector3i{size_z,size_x,size_y}, *this);
}


