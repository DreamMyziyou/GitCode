//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_VULKANRENDEREXPORT_H
#define WORLDENGINE_VULKANRENDEREXPORT_H

#ifdef _WIN32
#ifdef VULKANRENDER_BUILD
#define VULKANRENDER_API __declspec(dllexport)
#else
#define VULKANRENDER_API __declspec(dllimport)
#endif
#else
#define VULKANRENDER_API
#endif

#endif  // WORLDENGINE_VULKANRENDEREXPORT_H
