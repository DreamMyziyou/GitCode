//
// Created by WeslyChen on 2024/1/18.
//

#ifndef WORLDENGINE_MODULESINGLETON_H
#define WORLDENGINE_MODULESINGLETON_H

#include "ModuleCore.h"

#define SINGLETON_MODULE(CLASS_NAME)                                 \
public:                                                              \
    CLASS_NAME() = default;                                          \
    ~CLASS_NAME() = default;                                         \
    CLASS_NAME(const CLASS_NAME&) = delete;                          \
    CLASS_NAME& operator=(const CLASS_NAME&) = delete;               \
    static CLASS_NAME* instance()                                    \
    {                                                                \
        struct Impl                                                  \
        {                                                            \
            CLASS_NAME instance{};                                   \
            Impl()                                                   \
            {                                                        \
                ModuleCore::GetManager()->RegisterModule(&instance); \
            }                                                        \
        };                                                           \
        static Impl instance;                                        \
        return &(instance.instance);                                 \
    }

#endif  // WORLDENGINE_MODULESINGLETON_H
