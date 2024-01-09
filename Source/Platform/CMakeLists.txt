set(MODULE_NAME Platform)
make_module(${MODULE_NAME} .)
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Public)
target_link_libraries(${MODULE_NAME} PRIVATE Common)