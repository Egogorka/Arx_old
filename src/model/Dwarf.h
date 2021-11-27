//
// Created by Meevere on 26.11.2021.
//

#ifndef ARX_DWARF_H
#define ARX_DWARF_H

#include "utility/Vector.h"

class Dwarf {
public:
    Vector3i position;

    /**
     * Default range of health - 0 to 1000
     */
    int health;

    /**
     * Default range of hunger - 0 to 1000
     */
    int hunger;

    /**
     *  From 0 to whatever
     */
    int age;
public:

    Dwarf();

    explicit Dwarf(const Vector3i &position);
    explicit Dwarf(Vector3i && position);

    Dwarf(const Vector3i &position, int health, int hunger, int age);

//    [[nodiscard]] const Vector3i &getPosition() const;
//
//    [[nodiscard]] int getHealth() const;
//
//    [[nodiscard]] int getHunger() const;
//
//    [[nodiscard]] int getAge() const;
};


#endif //ARX_DWARF_H
