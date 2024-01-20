//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_ECSEXPORT_H
#define WORKENGINE_ECSEXPORT_H

#ifdef _WIN32
#ifdef ECS_BUILD
#define ECS_API __declspec(dllexport)
#else
#define ECS_API __declspec(dllimport)
#endif
#else
#define ECS_API
#endif

#endif  // WORKENGINE_ECSEXPORT_H
