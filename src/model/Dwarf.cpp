//
// Created by Meevere on 26.11.2021.
//

#include "Dwarf.h"

Dwarf::Dwarf(const Vector3i &position, int health, int hunger, int age) :
    Object(position),
    health(health), hunger(hunger), age(age), path() {}

Dwarf::Dwarf(const Vector3i &position) :
    Dwarf(position, 1000, 1000, 20) {}

Dwarf::Dwarf(Vector3i && position):
    Dwarf(position) {}

Dwarf::Dwarf():
    Dwarf(Vector3i{0,0,0}) {}

std::string Dwarf::getObjectType() {
    return "dwarf";
}

void Dwarf::update() {
    int d100 = rand() % 100;
    if (d100 < 80) return;

    if(path.empty()) {
        Vector3i rand_vector{0, rand() % 3 - 1, rand() % 3 - 1};
        position += rand_vector;

    } else {
        auto temp = path.front();
        position = Vector3i{0, temp.x(), temp.y()};
        path.pop_front();
    }
}

#include "utility/PathTo.h"

void Dwarf::go_to(const Vector3i &vec, const Container& container) {
    vector<vector<int>> map{};

    map.resize(container.getSize().x());
    for(auto& item : map){
        item = vector<int>(container.getSize().y(),-1);
    }

    for(auto& unit : container){
        if(unit.pos.z() != 0) continue;

        if(!unit.objects.empty()){
            map[unit.pos.x()][unit.pos.y()] = -2;
        }
    }

    path = PathTo(position.getXY(), vec.getXY(), map);
}

void Dwarf::break_at(const Vector3i &vec, const Container &container) {
    go_to(vec, container);
    _hasTask = true;
}

bool Dwarf::hasTask() {
    return _hasTask;
}

void Dwarf::setTask(bool task) {
    _hasTask = task;
}

//const Vector3i &Dwarf::getPosition() const { return position; }
//
//int Dwarf::getHealth() const { return health; }
//int Dwarf::getHunger() const { return hunger; }
//int Dwarf::getAge() const { return age; }
