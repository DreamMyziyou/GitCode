//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_APPEXPORT_H
#define WORLDENGINE_APPEXPORT_H

#ifdef _WIN32
#ifdef APP_BUILD
#define APP_API __declspec(dllexport)
#else
#define APP_API __declspec(dllimport)
#endif
#else
#define APP_API
#endif

#endif  // WORLDENGINE_APPEXPORT_H
