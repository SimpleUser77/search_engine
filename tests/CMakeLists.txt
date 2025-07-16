cmake_minimum_required(VERSION 3.30)

project(searchEngine_tests)

# Включаем модуль FetchContent
include(FetchContent)

# Объявляем загрузку googletest
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip)

# Включаем googletest в проект
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME} server_tests.cpp
        ${CMAKE_SOURCE_DIR}/src/invertedIndex.cpp
        ${CMAKE_SOURCE_DIR}/src/searchServer.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${gtest_SOURCE_DIR}/include ${INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}  PRIVATE gtest_main  nlohmann_json::nlohmann_json)
