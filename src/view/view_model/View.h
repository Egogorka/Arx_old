//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_VIEW_H
#define ARX_VIEW_H

#include <memory>
#include "src/view/drawer/Drawer.h"
#include "src/model/Object.h"

#include "src/model/structures/all.h"
#include "src/model/Cell.h"

class View {
    std::shared_ptr<Drawer> drawer;
    int scale = 1;

public:
    explicit View(std::shared_ptr<Drawer> drawer);

    void drawObject(std::shared_ptr<Object> object);
    void drawCell(const Cell& cell);

private:
    void drawEnvironment(std::shared_ptr<Environment> environment);
    void drawStorehouse(std::shared_ptr<Storehouse> storehouse);
//    void drawDwarf(std::shared_ptr<Resource>&& resource);
};


#endif //ARX_VIEW_H
