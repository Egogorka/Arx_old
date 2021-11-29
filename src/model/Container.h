//
// Created by Meevere on 27.11.2021.
//

#ifndef ARX_CONTAINER_H
#define ARX_CONTAINER_H

#include <vector>
#include <list>
#include <memory>

#include "src/model/Cell.h"
#include "src/model/Object.h"

#include "utility/Vector.h"

class Container {

    /**
     * Map of cells - the coordinates are z,x,y (z is height)
     */
    std::vector<std::vector<std::vector<Cell>>> map;

    /**
     * Map of objects via coordinates
     */
    std::vector<std::vector<std::vector<
            std::list<std::shared_ptr<Object>>
        >>> objects;

public:

    Container();
    Container(int size_z, int size_x, int size_y);

    std::list<std::shared_ptr<Object>>& get_at(const Vector3i& vec);
    std::list<std::shared_ptr<Object>>& get_at(int z, int x, int y);

    void add_at(const Vector3i& vec, std::shared_ptr<Object>&& object);
    void add_at(int z, int x, int y, std::shared_ptr<Object>&& object);

    bool empty_at(const Vector3i& vec);
    bool empty_at(int z, int x, int y);

    Cell& get_cell_at(const Vector3i& vec);
    Cell& get_cell_at(int z, int x, int y);

    std::vector<std::vector<Cell>>& getZSection(unsigned int z);

// TODO: Implement iterator support



// Const methods

    [[nodiscard]] const std::vector<std::vector<Cell>>& getZSection(unsigned int z) const;
    [[nodiscard]] const std::list<std::shared_ptr<Object>>& get_at(const Vector3i& vec) const;
    [[nodiscard]] const std::list<std::shared_ptr<Object>>& get_at(int z, int x, int y) const;

};


#endif //ARX_CONTAINER_H
