cmake_minimum_required(VERSION 3.5...3.14)

project(file_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(FC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")
# set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
# set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")

message("file_core")
message("${SRC_DIR}\n${LIB_DIR}")

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

find_package(Qt5 REQUIRED COMPONENTS Core Network)
include_directories(${FC_INCLUDE_PATH})

add_subdirectory(${FC_SOURCE_PATH})

message("Build file_core lib")
add_library(${PROJECT_NAME} ${FC_HEADERS} ${FC_SOURCES})

#-----include zlib library-----------------------------------
# add_subdirectory("${LIB_DIR}/zlib/" "${CMAKE_BINARY_DIR}/lib/zlib")
set(ZLIB_LIBRARY "${SRC_DIR}/libzlib1.dll")
set(ZLIB_INCLUDE "${LIB_DIR}/zlib")
set(ZCONF_INCLUDE "${CMAKE_BINARY_DIR}/lib/zlib/")


#-----include bzip2 library-----------------------------------
# add_subdirectory("${LIB_DIR}/bzip2/" "${CMAKE_BINARY_DIR}/lib/bzip2")
# set(BZIP2_LIBRARIES "${CMAKE_BINARY_DIR}/lib/bzip2/lib/libbzip2.dll")
# set(BZIP2_INCLUDE_DIR "${LIB_DIR}/bzip2/include")

#-----include quazip library----------------------------------
add_subdirectory("${LIB_DIR}/quazip/" "${CMAKE_BINARY_DIR}/lib/quazip")
set(QUAZIP_LIBRARY "${SRC_DIR}/libquazip1-qt5.dll")
set(QUAZIP_INCLUDE "${LIB_DIR}/quazip")

target_include_directories(${PROJECT_NAME}
    PRIVATE ${ZLIB_INCLUDE}
    PRIVATE ${QUAZIP_INCLUDE}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core Qt5::Network
    ${ZLIB_LIBRARY}
    ${QUAZIP_LIBRARY}
)
































