set(MODULE_NAME ECS)
make_shared_module(${MODULE_NAME} .)
target_include_directories(${MODULE_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${MODULE_NAME} PUBLIC
        Logger
        Module)