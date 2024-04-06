cmake_minimum_required(VERSION 3.5)

project(imap_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMAP_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(IMAP_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(IMAP_HEADERS
    ${IMAP_INCLUDE_PATH}/email.h
    ${IMAP_INCLUDE_PATH}/mail_request.h
    ${IMAP_INCLUDE_PATH}/simple_mail.h
    ${IMAP_INCLUDE_PATH}/mail.h
    ${IMAP_INCLUDE_PATH}/tools.h
    ${IMAP_INCLUDE_PATH}/variables.h
    ${IMAP_INCLUDE_PATH}/imap_client.h
)

set(IMAP_SOURCES
    ${IMAP_SOURCE_PATH}/tools.cpp
    ${IMAP_SOURCE_PATH}/simple_mail.cpp
    ${IMAP_SOURCE_PATH}/mail.cpp
    ${IMAP_SOURCE_PATH}/imap_client.cpp
)

find_package(Qt5 REQUIRED COMPONENTS Core Network Sql)
include_directories(${IMAP_INCLUDE_PATH})

add_subdirectory(${IMAP_SOURCE_PATH})

message("Build lib_imap_client")
add_library(${PROJECT_NAME} ${IMAP_HEADERS} ${IMAP_SOURCES})


target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network Qt5::Sql)
































