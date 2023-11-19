file(GLOB_RECURSE SOUCES_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SOUCES_CPP})

target_link_libraries(${PROJECT_NAME} PRIVATE Common)