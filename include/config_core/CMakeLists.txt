cmake_minimum_required(VERSION 3.5...3.14)

project(config_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CFG_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(CFG_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(CFG_HEADERS
    ${CFG_INCLUDE_PATH}/config.h
    ${CFG_INCLUDE_PATH}/cfg_variables.h
)

set(CFG_SOURCES
    ${CFG_SOURCE_PATH}/config.cpp
)































