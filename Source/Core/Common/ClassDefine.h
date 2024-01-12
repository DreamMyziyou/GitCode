//
// Created by chenwei on 2023/11/19.
//

#ifndef WORKENGINE_CLASSDEFINE_H
#define WORKENGINE_CLASSDEFINE_H


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


#endif//WORKENGINE_CLASSDEFINE_H
