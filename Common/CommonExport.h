//
// Created by chenwei on 2023/11/19.
//

#ifndef GITWORKSPACE_COMMONEXPORT_H
#define GITWORKSPACE_COMMONEXPORT_H

#ifdef COMMON_BUILD
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif

#endif//GITWORKSPACE_COMMONEXPORT_H
