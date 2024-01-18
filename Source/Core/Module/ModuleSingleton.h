//
// Created by WeslyChen on 2024/1/18.
//

#ifndef WORKENGINE_MODULESINGLETON_H
#define WORKENGINE_MODULESINGLETON_H

#include <memory>

#include "IModule.h"

#define SINGLETON_MODULE(CLASS_NAME)                            \
public:                                                        \
    CLASS_NAME() = default;                                     \
    ~CLASS_NAME() = default;                                    \
    CLASS_NAME(const CLASS_NAME&) = delete;                     \
    CLASS_NAME& operator=(const CLASS_NAME&) = delete;          \
                                                                \
public:                                                         \
    static std::shared_ptr<CLASS_NAME> instance()               \
    {                                                           \
        struct Impl                                             \
        {                                                       \
            std::shared_ptr<CLASS_NAME> instance;               \
            Impl()                                              \
            {                                                   \
                instance = std::make_shared<CLASS_NAME>();      \
                Module::GetManager()->RegisterModule(instance); \
            }                                                   \
        };                                                      \
        static Impl instance;                                   \
        return instance.instance;                               \
    }

#endif  // WORKENGINE_MODULESINGLETON_H
