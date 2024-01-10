//
// Created by chenwei on 2024/1/9.
//

#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(UnitTest, Test01)
{
    EXPECT_EQ(0, 0.0);
}