set(MODULE_NAME HelloWorld)
file(GLOB_RECURSE SOURCES_CPP ./*.cpp)
add_executable(${MODULE_NAME} ${SOURCES_CPP})

target_link_libraries(${MODULE_NAME} PRIVATE Core)