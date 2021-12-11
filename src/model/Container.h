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

using namespace std;

struct ContainerUnit {
    Cell cell;
    list<shared_ptr<Object>> objects;
    Vector3i pos;

    ContainerUnit();

    ContainerUnit(const Cell &cell);
    ContainerUnit(const Cell &cell, const Vector3i &pos);

    void add(shared_ptr<Object>&& object);
};

class Container {

    /**
     * Map of ContainerUnits
     */
    vector<vector<vector<ContainerUnit>>> map;

    int size_z;
    int size_x;
    int size_y;
public:
    vector<shared_ptr<Object>> objects;

    Container();
    Container(int size_z, int size_x, int size_y);

    ContainerUnit& get(int z, int x, int y);
    ContainerUnit& get(const Vector3i& vec);

    list<shared_ptr<Object>>& get_at(const Vector3i& vec);
    list<shared_ptr<Object>>& get_at(int z, int x, int y);

    void add_at(const Vector3i& vec, shared_ptr<Object>&& object);
    void add_at(int z, int x, int y, shared_ptr<Object>&& object);

    bool empty_at(const Vector3i& vec);
    bool empty_at(int z, int x, int y);

    Cell& get_cell_at(const Vector3i& vec);
    Cell& get_cell_at(int z, int x, int y);

    // Const methods

    Vector3i getSize() const;

    [[nodiscard]] const list<shared_ptr<Object>>& get_at(const Vector3i& vec) const;
    [[nodiscard]] const list<shared_ptr<Object>>& get_at(int z, int x, int y) const;

    [[nodiscard]] const ContainerUnit& get(int z, int x, int y) const;
    [[nodiscard]] const ContainerUnit& get(const Vector3i& vec) const;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Iterator support
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Usual iterator

    class Iterator {
        Vector3i pos;
        Container* container;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = ContainerUnit;
        using pointer           = ContainerUnit*;
        using reference         = ContainerUnit&;

        Iterator(const Vector3i& pos, Container& container);
        Iterator(Vector3i&& pos, Container& container);

        Iterator(const Iterator& it);
        Iterator& operator=(const Iterator& it);

        reference operator*() const;
        pointer operator->();

        Iterator operator++();
        const Iterator operator++(int);

        friend bool operator== (const Iterator& a, const Iterator& b);
        friend bool operator!= (const Iterator& a, const Iterator& b);
    };

    // ATTENTION
    // Code is just copied from Iterator - so if Iterator is in need of change - the so is the ConstIterator
    class ConstIterator {
        Vector3i pos;
        const Container* container;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = ContainerUnit;
        using pointer           = const ContainerUnit*;
        using reference         = const ContainerUnit&;

        ConstIterator(const Vector3i& pos, const Container& container);
        ConstIterator(Vector3i&& pos, const Container& container);

        ConstIterator(const ConstIterator& it);
        ConstIterator& operator=(const ConstIterator& it);

        reference operator*() const;
        pointer operator->();

        ConstIterator operator++();
        const ConstIterator operator++(int);

        friend bool operator== (const ConstIterator& a, const ConstIterator& b);
        friend bool operator!= (const ConstIterator& a, const ConstIterator& b);
    };

    Iterator begin();
    Iterator end();

    ConstIterator begin() const;
    ConstIterator end() const;
};


#endif //ARX_CONTAINER_H
