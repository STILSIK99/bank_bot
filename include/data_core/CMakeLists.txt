cmake_minimum_required(VERSION 3.5...3.14)

project(data_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(DC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(DC_HEADERS
    # ${DC_INCLUDE_PATH}/variables.h
    ${DC_INCLUDE_PATH}/data_base.h
    ${DC_INCLUDE_PATH}/data_storaga.h
    ${DC_INCLUDE_PATH}/data_core.h
)

set(DC_SOURCES
    ${DC_SOURCE_PATH}/data_base.cpp
    ${DC_SOURCE_PATH}/data_storage.cpp
    ${DC_SOURCE_PATH}/data_core.cpp
)































