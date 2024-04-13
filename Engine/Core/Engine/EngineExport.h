//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORLDENGINE_ENGINEEXPORT_H
#define WORLDENGINE_ENGINEEXPORT_H

#ifdef _WIN32
#ifdef ENGINE_BUILD
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif

#endif  // WORLDENGINE_ENGINEEXPORT_H
