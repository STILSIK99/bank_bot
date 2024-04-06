cmake_minimum_required(VERSION 3.5...3.14)

project(bank_bot LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SRC_LIB "${SRC_DIR}/lib")
set(BUILD_SHARED_LIBS ON)

#-----include shared --------------------------------------------------------
set(SHARED_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/shared/include")
set(SHARED_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/shared/source")
set(SHARED_HEADERS
    ${SHARED_INCLUDE_PATH}/statement.h
    ${SHARED_INCLUDE_PATH}/record.h
    ${SHARED_INCLUDE_PATH}/exceptions.h
    ${SHARED_INCLUDE_PATH}/tools.h
    ${SHARED_INCLUDE_PATH}/daily_operations.h
)
set(SHARED_SOURCES
    ${SHARED_SOURCE_PATH}/statement.cpp
    ${SHARED_SOURCE_PATH}/record.cpp
    ${SHARED_SOURCE_PATH}/tools.cpp
    ${SHARED_SOURCE_PATH}/daily_operations.cpp
)
#-----include imap core------------------------------------------------------
set(IMAP_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/imap/include")
set(IMAP_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/imap/source/")
set(IMAP_HEADERS
    ${IMAP_INCLUDE_PATH}/email.h
    ${IMAP_INCLUDE_PATH}/mail_request.h
    ${IMAP_INCLUDE_PATH}/simple_mail.h
    ${IMAP_INCLUDE_PATH}/mail.h
    ${IMAP_INCLUDE_PATH}/imap_tools.h
    ${IMAP_INCLUDE_PATH}/imap_variables.h
    ${IMAP_INCLUDE_PATH}/imap_client.h
)
set(IMAP_SOURCES
    ${IMAP_SOURCE_PATH}/tools.cpp
    ${IMAP_SOURCE_PATH}/simple_mail.cpp
    ${IMAP_SOURCE_PATH}/mail.cpp
    ${IMAP_SOURCE_PATH}/imap_client.cpp
)


#-----include parser core lib------------------------------------------------
set(PC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/parser_core/include")
set(PC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/parser_core/source")
set(PC_HEADERS
    ${PC_INCLUDE_PATH}/parser_core.h
    # ${PC_INCLUDE_PATH}/test.h
    ${PC_INCLUDE_PATH}/pc_tools.h
    ${PC_INCLUDE_PATH}/pc_variables.h
)
set(PC_SOURCES
    ${PC_SOURCE_PATH}/parser_core.cpp
    # ${PC_SOURCE_PATH}/test.cpp
    ${PC_SOURCE_PATH}/tools.cpp
)


#-----include file core lib--------------------------------------------------
set(FC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/file_core/include")
set(FC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/file_core/source")
set(FC_HEADERS
    ${FC_INCLUDE_PATH}/fc_variables.h
    ${FC_INCLUDE_PATH}/file_downloader.h
    ${FC_INCLUDE_PATH}/file_unzip.h
    ${FC_INCLUDE_PATH}/file_core.h
)
set(FC_SOURCES
    ${FC_SOURCE_PATH}/file_downloader.cpp
    ${FC_SOURCE_PATH}/file_unzip.cpp
    ${FC_SOURCE_PATH}/file_core.cpp
)


#-----include data core lib--------------------------------------------------
set(DC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/data_core/include")
set(DC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/data_core/source")
set(DC_HEADERS
    ${DC_INCLUDE_PATH}/data_base.h
    ${DC_INCLUDE_PATH}/data_storage.h
    ${DC_INCLUDE_PATH}/data_core.h
    ${DC_INCLUDE_PATH}/dc_variables.h
)
set(DC_SOURCES
    ${DC_SOURCE_PATH}/data_base.cpp
    ${DC_SOURCE_PATH}/data_storage.cpp
    ${DC_SOURCE_PATH}/data_core.cpp
)


#-----include control core lib--------------------------------------------------
set(CC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/control_core/include")
set(CC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/control_core/source")
set(CC_HEADERS
    ${CC_INCLUDE_PATH}/control_core.h
)
set(CC_SOURCES
    ${CC_SOURCE_PATH}/control_core.cpp
)


#-----include main sources------------------------------------------------------
set(HEADERS
    ${INCLUDE_PATH}/test.h
)
set(SOURCES
    main.cpp
    "${SOURCE_PATH}/test.cpp"
)

include_directories(
    "${FC_INCLUDE_PATH}"
    "${INCLUDE_PATH}"
    "${DC_INCLUDE_PATH}"
    "${CC_INCLUDE_PATH}"
    "${PC_INCLUDE_PATH}"
    "${IMAP_INCLUDE_PATH}"
    "${SHARED_INCLUDE_PATH}"
)


add_subdirectory("${SOURCE_PATH}")

add_executable(${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
  ${SHARED_HEADERS}
  ${SHARED_SOURCES}
  ${FC_SOURCES}
  ${FC_HEADERS}
  ${DC_SOURCES}
  ${DC_HEADERS}
  ${IMAP_HEADERS}
  ${IMAP_SOURCES}
  ${PC_HEADERS}
  ${PC_SOURCES}
)

#-----include Qt5 libs---------------------------------------
find_package(Qt5 REQUIRED COMPONENTS Core Network Sql)
# target_link_libraries(bank_bot Qt5::Core Qt5::Network Qt5::Sql)

#-----include imap lib---------------------------------------
# add_subdirectory("${LIB_DIR}/imap" "${CMAKE_CURRENT_BINARY_DIR}/lib/imap")
# set(IMAP_LIBRARY "${SRC_LIB}/libimap_client.dll")
# set(IMAP_INCLUDE "${LIB_DIR}/imap/include")

#-----include zlib lib---------------------------------------
set(ZLIB_LIBRARY "${SRC_LIB}/libzlib1.dll")
set(ZLIB_INCLUDE "${LIB_DIR}/zlib")
set(ZCONF_INCLUDE "${CMAKE_BINARY_DIR}/lib/zlib/")

#-----include quazip lib-------------------------------------
set(QUAZIP_LIBRARY "${SRC_LIB}/libquazip1-qt5.dll")
set(QUAZIP_INCLUDE "${LIB_DIR}/quazip")

#-----include file core libs---------------------------------
# add_subdirectory("${LIB_DIR}/file_core" "${CMAKE_BINARY_DIR}/lib/file_core")
# set(FILE_CORE_LIBRARY "${CMAKE_BINARY_DIR}/lib/file_core/libfile_core.dll")
# set(FILE_CORE_INCLUDE "${LIB_DIR}/file_core/include")

#-----include parser core lib--------------------------------
# add_subdirectory("${LIB_DIR}/parser_core" "${CMAKE_BINARY_DIR}/lib/parser_core")
# set(PARSER_CORE_LIBRARY "${SRC_LIB}/libparser_core.dll")
# set(PARSER_CORE_INCLUDE "${LIB_DIR}/parser_core/include")




target_include_directories(${PROJECT_NAME}
    # PRIVATE ${IMAP_INCLUDE}
    # PRIVATE ${PARSER_CORE_INCLUDE}
    PRIVATE ${QUAZIP_INCLUDE}
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt5::Core Qt5::Network Qt5::Sql
    # PRIVATE ${IMAP_LIBRARY}
    # PRIVATE ${PARSER_CORE_LIBRARY}
    PRIVATE ${QUAZIP_LIBRARY}
)


#-----install------------------------------------------------
include(GNUInstallDirs)
install(TARGETS bank_bot
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
