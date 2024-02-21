set(MODULE_NAME Engine)
make_shared_module(${MODULE_NAME} .)
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${MODULE_NAME} PUBLIC
        Platform
        Geometry
        Logger
        ModuleCore
        SignalCenter
        World)