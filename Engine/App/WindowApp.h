//
// Created by WeslyChen on 2024/1/29.
//
#ifndef WORLDENGINE_WINDOWAPP_H
#define WORLDENGINE_WINDOWAPP_H

#include "App.h"

class APP_API WindowApp : public App
{
protected:
    WindowApp();
    ~WindowApp() override;
    WindowApp(const WindowApp&) = delete;
    WindowApp& operator=(const WindowApp&) = delete;

public:
    void Run() override;

private:
    struct Impl;
    Impl* mImpl = nullptr;
};

#endif  // WORLDENGINE_WINDOWAPP_H
