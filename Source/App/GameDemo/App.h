//
// Created by WeslyChen on 2024/1/14.
//

#ifndef WORKENGINE_APP_H
#define WORKENGINE_APP_H

#include "Common/ClassMacro.h"

class App final
{
    SINGLETON_CLASS(App)

public:
    void Start();
    void Run();
    void Stop();

private:
};

#endif  // WORKENGINE_APP_H
