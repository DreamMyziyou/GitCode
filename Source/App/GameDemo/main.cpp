//
// Created by WeslyChen on 2024/1/14.
//

#include "App.h"

int main(int argc, char** argv)
{
    App::instance().Init();
    App::instance().Run();
    return 0;
}