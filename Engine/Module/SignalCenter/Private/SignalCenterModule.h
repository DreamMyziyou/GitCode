//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_SIGNALCENTERMODULE_H
#define WORKENGINE_SIGNALCENTERMODULE_H

#include "Module/ModuleCore/ModuleSingleton.h"
#include "SignalCenter.h"

class SignalCenterModule final : public ModuleCore::IModule, public SignalCenter::ICenter
{
    SINGLETON_MODULE(SignalCenterModule)

private:
};

#endif  // WORKENGINE_SIGNALCENTERMODULE_H
