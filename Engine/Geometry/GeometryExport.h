//
// Created by WeslyChen on 2024/2/3.
//
#ifndef WORLDENGINE_GEOMETRYEXPORT_H
#define WORLDENGINE_GEOMETRYEXPORT_H

#ifdef _WIN32
#ifdef GEOMETRY_BUILD
#define GEOMETRY_API __declspec(dllexport)
#else
#define GEOMETRY_API __declspec(dllimport)
#endif
#else
#define GEOMETRY_API
#endif

#endif  // WORLDENGINE_GEOMETRYEXPORT_H
