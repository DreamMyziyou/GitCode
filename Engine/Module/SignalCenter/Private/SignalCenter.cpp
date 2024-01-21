//
// Created by WeslyChen on 2024/1/20.
//

#include "SignalCenter.h"

#include "SignalCenterModule.h"

SignalCenter::ICenter* SignalCenter::GetCenter()
{
    return SignalCenterModule::instance();
}
