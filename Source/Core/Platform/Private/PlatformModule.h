//
// Created by chenwei on 2024/1/9.
//

#ifndef GITWORKSPACE_PLATFORMMODULE_H
#define GITWORKSPACE_PLATFORMMODULE_H

#include "Common/ClassDefine.h"
#include "Common/IModule.h"
#include "PlatformExport.h"

class PLATFORM_API PlatformModule : public IModule
{
    SINGLETON_CLASS(PlatformModule)
};

#endif  // GITWORKSPACE_PLATFORMMODULE_H
