//
// Created by chenwei on 2023/11/19.
//

#ifndef GITWORKSPACE_MODULECOREEXPORT_H
#define GITWORKSPACE_MODULECOREEXPORT_H

#ifdef _WIN32
#ifdef MODULECORE_BUILD
#define MODULECORE_API __declspec(dllexport)
#else
#define MODULECORE_API __declspec(dllimport)
#endif
#else
#define MODULECORE_API
#endif

#endif  // GITWORKSPACE_MODULECOREEXPORT_H
