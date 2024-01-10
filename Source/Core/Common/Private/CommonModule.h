//
// Created by chenwei on 2023/11/19.
//

#ifndef GITWORKSPACE_COMMONMODULE_H
#define GITWORKSPACE_COMMONMODULE_H

#include "ClassDefine.h"
#include "CommonExport.h"
#include "IModule.h"

class COMMON_API CommonModule : public IModule
{
    SINGLETON_CLASS(CommonModule)
};


#endif//GITWORKSPACE_COMMONMODULE_H
