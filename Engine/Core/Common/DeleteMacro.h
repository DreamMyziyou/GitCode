//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORLDENGINE_DELETEMACRO_H
#define WORLDENGINE_DELETEMACRO_H

#define SAFE_DELETE(ptr) \
    delete ptr;          \
    ptr = nullptr

#endif  // WORLDENGINE_DELETEMACRO_H
