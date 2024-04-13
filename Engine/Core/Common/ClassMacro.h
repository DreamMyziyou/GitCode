//
// Created by chenwei on 2023/11/19.
//

#ifndef WORLDENGINE_CLASSMACRO_H
#define WORLDENGINE_CLASSMACRO_H

#define SINGLETON_CLASS(CLASS_NAME)                    \
private:                                               \
    CLASS_NAME() = default;                            \
    ~CLASS_NAME() = default;                           \
    CLASS_NAME(const CLASS_NAME&) = delete;            \
    CLASS_NAME& operator=(const CLASS_NAME&) = delete; \
                                                       \
public:                                                \
    static CLASS_NAME* instance()                      \
    {                                                  \
        static CLASS_NAME gInstance;                   \
        return &gInstance;                             \
    }

#define SINGLETON_CLASS_CUSTOM_CONSTRUCT(CLASS_NAME)   \
private:                                               \
    CLASS_NAME();                                      \
    ~CLASS_NAME();                           \
    CLASS_NAME(const CLASS_NAME&) = delete;            \
    CLASS_NAME& operator=(const CLASS_NAME&) = delete; \
                                                       \
public:                                                \
    static CLASS_NAME* instance()                      \
    {                                                  \
        static CLASS_NAME gInstance;                   \
        return &gInstance;                             \
    }

#endif  // WORLDENGINE_CLASSMACRO_H
