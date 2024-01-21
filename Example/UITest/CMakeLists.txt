set(MODULE_NAME UITest)
file(GLOB_RECURSE SOURCES_CPP ./*.cpp)
add_executable(${MODULE_NAME} ${SOURCES_CPP})

target_link_libraries(${MODULE_NAME} PRIVATE App Window)

file(GLOB DLL_FILES ${CMAKE_SOURCE_DIR}/ThirdParty/glfw/lib-vc2022/*.dll)
foreach (DLL_FILE ${DLL_FILES})
    add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL_FILE}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endforeach ()