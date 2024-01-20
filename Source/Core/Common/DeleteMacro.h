//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_DELETEMACRO_H
#define WORKENGINE_DELETEMACRO_H

#define SAFE_DELETE(ptr) \
    delete ptr;          \
    ptr = nullptr;

#endif  // WORKENGINE_DELETEMACRO_H
