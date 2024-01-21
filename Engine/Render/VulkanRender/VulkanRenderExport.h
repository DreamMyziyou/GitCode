//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANRENDEREXPORT_H
#define WORKENGINE_VULKANRENDEREXPORT_H

#ifdef _WIN32
#ifdef VULKANRENDER_BUILD
#define VULKANRENDER_API __declspec(dllexport)
#else
#define VULKANRENDER_API __declspec(dllimport)
#endif
#else
#define VULKANRENDER_API
#endif

#endif  // WORKENGINE_VULKANRENDEREXPORT_H
