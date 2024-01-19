cmake_minimum_required(VERSION 3.16)

project(WorkEngine)

include(CmakeUtils/ModuleFunction.cmake)

set(BOOST_ROOT "D:/boost")
find_package(Boost 1.84.0 COMPONENTS log REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

include_directories(${CMAKE_CURRENT_LIST_DIR}/ThirdParty)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Source/Core)

add_subdirectory(ThirdParty)
add_subdirectory(Source)