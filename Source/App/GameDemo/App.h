//
// Created by WeslyChen on 2024/1/14.
//

#ifndef WORKENGINE_APP_H
#define WORKENGINE_APP_H

#include "Common/ClassDefine.h"

class App final
{
    SINGLETON_CLASS(App)

public:
    void Init();
    void Run();

private:
};

#endif  // WORKENGINE_APP_H
