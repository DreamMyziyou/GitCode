//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_APP_H
#define WORKENGINE_APP_H

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

#endif  // WORKENGINE_APP_H
