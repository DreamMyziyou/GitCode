function(make_module MODULE_NAME MODULE_DIR)
    # 添加编译宏
    set(BUILD_DEFINITION "${MODULE_NAME}_build")
    string(TOUPPER ${BUILD_DEFINITION} BUILD_DEFINITION)
    add_compile_definitions(${BUILD_DEFINITION})
    # 生成动态库
    file(GLOB_RECURSE CPP_SOURCES ${MODULE_DIR}/*.cpp)
    add_library(${MODULE_NAME} SHARED ${CPP_SOURCES})
endfunction()