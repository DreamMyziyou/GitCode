//
// Created by chenwei on 2023/11/19.
//

#ifndef WORKENGINE_COMMONEXPORT_H
#define WORKENGINE_COMMONEXPORT_H


#ifdef _WIN32
#ifdef COMMON_BUILD
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif
#else
#define COMMON_API
#endif


#endif//WORKENGINE_COMMONEXPORT_H
