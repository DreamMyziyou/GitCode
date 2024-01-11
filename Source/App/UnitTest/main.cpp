//
// Created by chenwei on 2024/1/9.
//

#include "Core.h"
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(UnitTest, Test01)
{
    int32 test01 = 1;
    int test02 = 1;

    EXPECT_TRUE(test01 == test02);
}