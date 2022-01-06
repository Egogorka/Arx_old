//
// Created by Meevere on 06.01.2022.
//

#include "ndArray.h"
#include <iostream>

using std::cout, std::endl;

int testNdArray() {

    cout << "Constructing array with {4,3,2}";
    auto test = ndArray<int, 3>::with_size({4, 3, 2});

    cout << "Filling array with increasing sequence\n";
    int counter = 0;
    for (auto &item : test) {
        item = counter++;
    }

    // Testing iterator
    cout << "Output via iterator\n";
    for (auto &item : test) {
        cout << item << ' ';
    }
    cout << endl;


    cout << "Test one vector access\n";
    cout << test(Vector3i{3, 0, 0}) << endl;

    cout << "Output via nested for and vector access\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 2; ++k) {
                cout << test(Vector3i{i,j,k}) << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
    cout << endl;

    cout << "Test get_section method\n";
    auto section = test.get_section(1);
    for (auto &item : section) {
        cout << item << ' ';
    }
    cout << endl;

    cout << "Test get_section of section\n";
    auto section2 = section.get_section(1);
    for (auto &item : section2) {
        cout << item << ' ';
    }
    cout << endl;

    return 0;
}
