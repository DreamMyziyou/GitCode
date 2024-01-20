//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_WINDOWEXPORT_H
#define WORKENGINE_WINDOWEXPORT_H

#ifdef _WIN32
#ifdef WINDOW_BUILD
#define WINDOW_API __declspec(dllexport)
#else
#define WINDOW_API __declspec(dllimport)
#endif
#else
#define WINDOW_API
#endif

#endif  // WORKENGINE_WINDOWEXPORT_H
