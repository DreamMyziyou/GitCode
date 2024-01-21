//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_RENDERMANAGEREXPORT_H
#define WORKENGINE_RENDERMANAGEREXPORT_H

#ifdef _WIN32
#ifdef RENDERMANAGER_BUILD
#define RENDERMANAGER_API __declspec(dllexport)
#else
#define RENDERMANAGER_API __declspec(dllimport)
#endif
#else
#define RENDERMANAGER_API
#endif

#endif  // WORKENGINE_RENDERMANAGEREXPORT_H
