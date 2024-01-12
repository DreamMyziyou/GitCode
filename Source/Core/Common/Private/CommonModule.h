//
// Created by chenwei on 2023/11/19.
//

#ifndef WORKENGINE_COMMONMODULE_H
#define WORKENGINE_COMMONMODULE_H


#include "Core/Common/ClassDefine.h"
#include "Core/Common/CommonExport.h"
#include "Core/Common/IModule.h"

class COMMON_API CommonModule : public IModule
{
    SINGLETON_CLASS(CommonModule)
};


#endif//WORKENGINE_COMMONMODULE_H
