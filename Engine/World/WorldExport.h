//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_WORLDEXPORT_H
#define WORKENGINE_WORLDEXPORT_H

#ifdef _WIN32
#ifdef WORLD_BUILD
#define WORLD_API __declspec(dllexport)
#else
#define WORLD_API __declspec(dllimport)
#endif
#else
#define WORLD_API
#endif

#endif  // WORKENGINE_WORLDEXPORT_H
