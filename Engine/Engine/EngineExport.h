//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_ENGINEEXPORT_H
#define WORKENGINE_ENGINEEXPORT_H

#ifdef _WIN32
#ifdef ENGINE_BUILD
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif

#endif  // WORKENGINE_ENGINEEXPORT_H
