//
// Created by chenwei on 2023/11/19.
//

#ifndef GITWORKSPACE_LOGGEREXPORT_H
#define GITWORKSPACE_LOGGEREXPORT_H

#ifdef _WIN32
#ifdef LOGGER_BUILD
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif
#else
#define LOGGER_API
#endif

#endif  // GITWORKSPACE_LOGGEREXPORT_H
