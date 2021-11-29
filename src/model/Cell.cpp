//
// Created by Meevere on 24.11.2021.
//

#include "Cell.h"


Cell::Cell(Cell::MaterialType floorType, Cell::MaterialType wallType, const Vector3i &position)
: floor_type(floorType), wall_type(wallType), position(position) {}

Cell::Cell(const Vector3i &position) : Cell(MaterialType::Grass, MaterialType::None, position) {}

Cell::Cell() : Cell(Vector3i{0,0,0}) {}

