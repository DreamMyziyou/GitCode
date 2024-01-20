//
// Created by WeslyChen on 2024/1/20.
//

#include "Application.h"

int main(int argc, char** argv)
{
    Application::instance()->Start();
    Application::instance()->Run();
    Application::instance()->Stop();
    return 0;
}