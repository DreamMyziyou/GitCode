//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_SIGNALCENTEREXPORT_H
#define WORKENGINE_SIGNALCENTEREXPORT_H

#ifdef _WIN32
#ifdef SIGNALCENTER_BUILD
#define SIGNALCENTER_API __declspec(dllexport)
#else
#define SIGNALCENTER_API __declspec(dllimport)
#endif
#else
#define SIGNALCENTER_API
#endif

#endif  // WORKENGINE_SIGNALCENTEREXPORT_H
