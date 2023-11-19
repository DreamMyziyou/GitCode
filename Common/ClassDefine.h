//
// Created by chenwei on 2023/11/19.
//

#ifndef GITWORKSPACE_CLASSDEFINE_H
#define GITWORKSPACE_CLASSDEFINE_H

#define SINGLETON_CLASS(CLASS_NAME)                    \
private:                                               \
    CLASS_NAME() = default;                            \
    ~CLASS_NAME() = default;                           \
    CLASS_NAME(const CLASS_NAME&) = delete;            \
    CLASS_NAME& operator=(const CLASS_NAME&) = delete; \
                                                       \
public:                                                \
    static CLASS_NAME& instance()                      \
    {                                                  \
        static CLASS_NAME gInstance;                   \
        return gInstance;                              \
    }
#endif//GITWORKSPACE_CLASSDEFINE_H
