file(GLOB_RECURSE SOUCES_CPP ./*.cpp)
add_executable(${PROJECT_NAME} ${SOUCES_CPP})

target_link_libraries(${PROJECT_NAME} PRIVATE Common)