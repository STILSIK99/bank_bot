cmake_minimum_required(VERSION 3.5...3.14)

project(file_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(FC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")
# set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
# set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")

set(FC_HEADERS
    ${FC_INCLUDE_PATH}/variables.h
    ${FC_INCLUDE_PATH}/file_downloader.h
    ${FC_INCLUDE_PATH}/file_unzip.h
    ${FC_INCLUDE_PATH}/file_core.h
)

set(FC_SOURCES
    ${FC_SOURCE_PATH}/file_downloader.cpp
    ${FC_SOURCE_PATH}/file_unzip.cpp
    ${FC_SOURCE_PATH}/file_core.cpp
)































