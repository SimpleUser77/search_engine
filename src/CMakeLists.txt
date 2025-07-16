cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/config.json")
    message(FATAL_ERROR "config.json is missing in the project root directory.")
endif()

add_custom_target(copy_files ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/resourses
    COMMAND ${CMAKE_COMMAND} -E copy
         ${CMAKE_SOURCE_DIR}/resourses/file001.txt
         ${CMAKE_SOURCE_DIR}/resourses/file002.txt
         ${CMAKE_SOURCE_DIR}/resourses/file003.txt
         ${CMAKE_SOURCE_DIR}/resourses/file004.txt
         ${CMAKE_BINARY_DIR}/resourses
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config.json
        ${CMAKE_SOURCE_DIR}/requests.json
       #${CMAKE_SOURCE_DIR}/answers.json
        ${CMAKE_BINARY_DIR}/src
     DEPENDS ${CMAKE_SOURCE_DIR}/resourses/file001.txt
     DEPENDS ${CMAKE_SOURCE_DIR}/resourses/file002.txt
     DEPENDS ${CMAKE_SOURCE_DIR}/resourses/file003.txt
     DEPENDS ${CMAKE_SOURCE_DIR}/resourses/file004.txt
     DEPENDS ${CMAKE_SOURCE_DIR}/config.json
     DEPENDS ${CMAKE_SOURCE_DIR}/requests.json
     #DEPENDS ${CMAKE_SOURCE_DIR}/answers.json
    )

add_executable(search_engine main.cpp ${INCLUDE_DIR}/converterJSON.h converterJSON.cpp
                                      ${INCLUDE_DIR}/invertedIndex.h invertedIndex.cpp
                                      ${INCLUDE_DIR}/searchServer.h searchServer.cpp)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(search_engine PUBLIC ${INCLUDE_DIR})