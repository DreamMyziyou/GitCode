set(MODULE_NAME Platform)
make_static_module(${MODULE_NAME} .)
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Public)