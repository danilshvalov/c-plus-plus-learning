cmake_minimum_required(VERSION 3.0.0)
project(final-first VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_executable(final-first main.cpp date.h date.cpp database.h database.cpp exceptions.cpp exceptions.h)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
