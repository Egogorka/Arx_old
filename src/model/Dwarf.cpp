//
// Created by Meevere on 26.11.2021.
//

#include "Dwarf.h"

Dwarf::Dwarf(const Vector3i &position) :
position(position), health(1000), hunger(1000), age(20) {}

Dwarf::Dwarf(const Vector3i &position, int health, int hunger, int age) :
position(position), health(health), hunger(hunger), age(age) {}

Dwarf::Dwarf(Vector3i && position): Dwarf(position) {}

Dwarf::Dwarf(): Dwarf(Vector3i{0,0,0}) {}

std::string Dwarf::getObjectType() {
    return "dwarf";
}

void Dwarf::update() {
    int d100 = rand() % 100;
    if ( d100 > 90 ){
        Vector3i rand_vector{rand() % 3 - 1, rand() % 3 - 1, rand() % 3 - 1};
        position += rand_vector;
    }
}

//const Vector3i &Dwarf::getPosition() const { return position; }
//
//int Dwarf::getHealth() const { return health; }
//int Dwarf::getHunger() const { return hunger; }
//int Dwarf::getAge() const { return age; }
