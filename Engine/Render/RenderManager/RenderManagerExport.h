//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_RENDERMANAGEREXPORT_H
#define WORLDENGINE_RENDERMANAGEREXPORT_H

#ifdef _WIN32
#ifdef RENDERMANAGER_BUILD
#define RENDERMANAGER_API __declspec(dllexport)
#else
#define RENDERMANAGER_API __declspec(dllimport)
#endif
#else
#define RENDERMANAGER_API
#endif

#endif  // WORLDENGINE_RENDERMANAGEREXPORT_H
