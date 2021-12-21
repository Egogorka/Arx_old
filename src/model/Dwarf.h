//
// Created by Meevere on 26.11.2021.
//

#ifndef ARX_DWARF_H
#define ARX_DWARF_H

#include "utility/Vector.h"
#include "Object.h"

#include "src/model/Container.h"

class Dwarf : public Object{
private:
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

    list<Vector2i> path;
    bool _hasTask;
public:
    std::string getObjectType() override;

    Dwarf();

    explicit Dwarf(const Vector3i &position);
    explicit Dwarf(Vector3i && position);

    Dwarf(const Vector3i &position, int health, int hunger, int age);

    void update() override;

    void go_to(const Vector3i &position, const Container& container);
    void break_at(const Vector3i &position, const Container& container);
    bool hasTask();
    // splint
    void setTask(bool task);
};


#endif //ARX_DWARF_H
