//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORLDENGINE_SIGNALCENTEREXPORT_H
#define WORLDENGINE_SIGNALCENTEREXPORT_H

#ifdef _WIN32
#ifdef SIGNALCENTER_BUILD
#define SIGNALCENTER_API __declspec(dllexport)
#else
#define SIGNALCENTER_API __declspec(dllimport)
#endif
#else
#define SIGNALCENTER_API
#endif

#endif  // WORLDENGINE_SIGNALCENTEREXPORT_H
