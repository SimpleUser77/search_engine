cmake_minimum_required(VERSION 3.30)
project(search_engine)
set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(RESOURCES ${CMAKE_SOURCE_DIR}/res)

add_subdirectory(src)
add_subdirectory(tests)
