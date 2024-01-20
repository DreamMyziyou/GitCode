//
// Created by chenwei on 2024/1/9.
//

#include <gtest/gtest.h>

#include "Logger/Logger.h"

int main(int argc, char* argv[])
{
    Logger::DisableLogger();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}