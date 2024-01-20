//
// Created by WeslyChen on 2024/1/20.
//

#include <gtest/gtest.h>

#include "SignalCenter/SignalCenter.h"

TEST(SignalCenter, SigToConn)
{
    SignalCenter::Signal<void()> signal;
    bool isHit = false;
    auto testFun = [&isHit]() { isHit = true; };
    signal.connect(testFun);
    signal();

    EXPECT_TRUE(isHit);
}