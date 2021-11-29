//
// Created by Meevere on 24.11.2021.
//

#ifndef ARX_CELL_H
#define ARX_CELL_H

#include "utility/Vector.h"

struct Cell {
    enum class MaterialType {
        None,
        Stone,
        Grass
    };

    MaterialType floor_type;
    MaterialType wall_type;

    Vector3i position;

    Cell();
    Cell(const Vector3i &position);

    Cell(MaterialType floorType, MaterialType wallType, const Vector3i &position);
};


#endif //ARX_CELL_H
