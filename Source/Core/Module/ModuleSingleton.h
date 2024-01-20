//
// Created by WeslyChen on 2024/1/18.
//

#ifndef WORKENGINE_MODULESINGLETON_H
#define WORKENGINE_MODULESINGLETON_H

#include "Module.h"

#define SINGLETON_MODULE(CLASS_NAME)                             \
public:                                                          \
    CLASS_NAME() = default;                                      \
    ~CLASS_NAME() = default;                                     \
    CLASS_NAME(const CLASS_NAME&) = delete;                      \
    CLASS_NAME& operator=(const CLASS_NAME&) = delete;           \
    static CLASS_NAME* instance()                                \
    {                                                            \
        struct Impl                                              \
        {                                                        \
            CLASS_NAME instance{};                               \
            Impl()                                               \
            {                                                    \
                Module::GetManager()->RegisterModule(&instance); \
            }                                                    \
        };                                                       \
        static Impl instance;                                    \
        return &(instance.instance);                             \
    }

#endif  // WORKENGINE_MODULESINGLETON_H
