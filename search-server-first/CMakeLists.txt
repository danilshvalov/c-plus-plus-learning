cmake_minimum_required(VERSION 3.0.0)
project(search-server-first VERSION 0.1.0)

include(CTest)
enable_testing()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
add_executable(search-server-first main.cpp iterator_range.h parse.h parse.cpp search_server.cpp search_server.h test_runner.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
