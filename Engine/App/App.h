//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_APP_H
#define WORLDENGINE_APP_H

#include "AppExport.h"

class APP_API App
{
protected:
    App();
    virtual ~App();
    App(const App&) = delete;
    App& operator=(const App&) = delete;

public:
    virtual void Run() = 0;
};

#endif  // WORLDENGINE_APP_H
