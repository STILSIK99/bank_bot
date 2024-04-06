cmake_minimum_required(VERSION 3.5...3.14)

project(control_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(CC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(CC_HEADERS
    # ${CC_INCLUDE_PATH}/variables.h
    ${CC_INCLUDE_PATH}/data_base.h
    ${CC_INCLUDE_PATH}/data_storaga.h
    ${CC_INCLUDE_PATH}/data_core.h
)

set(CC_SOURCES
    ${CC_SOURCE_PATH}/data_base.cpp
    ${CC_SOURCE_PATH}/data_storage.cpp
    ${CC_SOURCE_PATH}/data_core.cpp
)































