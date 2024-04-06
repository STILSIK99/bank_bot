cmake_minimum_required(VERSION 3.5...3.14)

project(bzip2 VERSION 0.1 LANGUAGES CXX C)

set(BZIP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(BZIP2_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/")

if (${BUILD_SHARED_LIBS})
    set(BUILD_SHARED_LIBS ON)
endif()

set(BZIP2_SRC
    ${BZIP2_SOURCE}/blocksort.c
    ${BZIP2_SOURCE}/bzlib.c
    ${BZIP2_SOURCE}/compress.c
    ${BZIP2_SOURCE}/crctable.c
    ${BZIP2_SOURCE}/decompress.c
    ${BZIP2_SOURCE}/huffman.c
    ${BZIP2_SOURCE}/randtable.c
)

set(BZIP2_HDR
    ${BZIP2_INCLUDE}/bzlib.h
    ${BZIP2_INCLUDE}/bzlib_private.h
)

include_directories(${BZIP2_INCLUDE})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/source/")

add_library(${PROJECT_NAME} SHARED ${BZIP2_SRC} ${BZIP2_HDR})
