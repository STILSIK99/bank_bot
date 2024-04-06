cmake_minimum_required(VERSION 3.5...3.14)

project(parser_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(PC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(PC_HEADERS
    ${PC_INCLUDE_PATH}/parser_core.h
    ${PC_INCLUDE_PATH}/test.h
    ${PC_INCLUDE_PATH}/tools.h
    ${PC_INCLUDE_PATH}/variables.h
)

set(PC_SOURCES
    ${PC_SOURCE_PATH}/parser_core.cpp
    ${PC_SOURCE_PATH}/test.cpp
    ${PC_SOURCE_PATH}/tools.cpp
)

find_package(Qt5 REQUIRED COMPONENTS Core Network Sql)
include_directories(${PC_INCLUDE_PATH})

add_subdirectory(${PC_SOURCE_PATH})

message("Build parser_core lib")
add_library(${PROJECT_NAME} ${PC_HEADERS} ${PC_SOURCES})


target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network Qt5::Sql)
































