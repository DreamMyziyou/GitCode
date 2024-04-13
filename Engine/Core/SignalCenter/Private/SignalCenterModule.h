//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORLDENGINE_SIGNALCENTERMODULE_H
#define WORLDENGINE_SIGNALCENTERMODULE_H

#include "Core/ModuleCore/ModuleSingleton.h"
#include "SignalCenter.h"

class SignalCenterModule final : public ModuleCore::IModule, public SignalCenter::ICenter
{
    SINGLETON_MODULE(SignalCenterModule)

private:
};

#endif  // WORLDENGINE_SIGNALCENTERMODULE_H
