//
// Created by chenwei on 2023/11/19.
//

#ifndef GITWORKSPACE_MODULEEXPORT_H
#define GITWORKSPACE_MODULEEXPORT_H

#ifdef _WIN32
#ifdef MODULE_BUILD
#define MODULE_API __declspec(dllexport)
#else
#define MODULE_API __declspec(dllimport)
#endif
#else
#define MODULE_API
#endif

#endif  // GITWORKSPACE_MODULEEXPORT_H
