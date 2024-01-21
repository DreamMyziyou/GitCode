//
// Created by chenwei on 2023/11/19.
//

#ifndef GITWORKSPACE_PLATFORMEXPORT_H
#define GITWORKSPACE_PLATFORMEXPORT_H

#ifdef _WIN32
#ifdef PLATFORM_BUILD
#define PLATFORM_API __declspec(dllexport)
#else
#define PLATFORM_API __declspec(dllimport)
#endif
#else
#define PLATFORM_API
#endif

#endif  // GITWORKSPACE_PLATFORMEXPORT_H
