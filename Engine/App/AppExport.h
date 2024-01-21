//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_APPEXPORT_H
#define WORKENGINE_APPEXPORT_H

#ifdef _WIN32
#ifdef APP_BUILD
#define APP_API __declspec(dllexport)
#else
#define APP_API __declspec(dllimport)
#endif
#else
#define APP_API
#endif

#endif  // WORKENGINE_APPEXPORT_H
