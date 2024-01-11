//
// Created by WeslyChen on 2024/1/11.
//

#ifndef WORKENGINE_COREEXPORT_H
#define WORKENGINE_COREEXPORT_H


#ifdef _WIN32
#ifdef CORE_BUILD
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif
#else
#define CORE_API
#endif


#endif//WORKENGINE_COREEXPORT_H
