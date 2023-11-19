//
// Created by chenwei on 2023/11/19.
//

#ifndef GITWORKSPACE_COMMONMODULE_H
#define GITWORKSPACE_COMMONMODULE_H

#include "ClassDefine.h"
#include "CommonExport.h"

class COMMON_API CommonModule
{
    SINGLETON_CLASS(CommonModule)

public:
    void test();
};


#endif//GITWORKSPACE_COMMONMODULE_H
