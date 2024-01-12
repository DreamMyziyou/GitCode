set(MODULE_NAME BasicType)
make_static_module(${MODULE_NAME} .)
target_include_directories(${MODULE_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})