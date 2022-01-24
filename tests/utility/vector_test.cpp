//
// Created by Meevere on 24.01.2022.
//

#include "utility/Vector.h"
#include <gtest/gtest.h>

TEST(vector_test, basics){
    Vector3i v1{1,2,3};
    Vector3i v2{3,2,1};

    Vector3i v3{-2,-4,-6};

    // Test coords
    ASSERT_EQ(v1.z(), 1);
    ASSERT_EQ(v1.x(), 2);
    ASSERT_EQ(v1.y(), 3);

    // Test addition
    ASSERT_EQ((v1 + v2), (Vector3i{4,4,4}));
    ASSERT_EQ((v1 - v2), (Vector3i{-2,0,2}));

    // Test multiplication
    ASSERT_EQ(v1*(-2), v3);

    // Test square
    ASSERT_EQ(v1.square(), 14);

    // Test subvector
    EXPECT_EQ((get_subvector<int, 2>(v1, 0)), (Vector2i{2,3}));
    EXPECT_EQ((get_subvector<int, 2>(v1, 1)), (Vector2i{1,3}));

    // Test constructor
    EXPECT_EQ((Vector3i::all(1)), (Vector3i{1,1,1}));
}