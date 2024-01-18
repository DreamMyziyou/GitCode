//
// Created by WeslyChen on 2024/1/14.
//

#include "App.h"

int main(int argc, char** argv)
{
    App::instance()->Start();
    App::instance()->Run();
    App::instance()->Stop();
    return 0;
}