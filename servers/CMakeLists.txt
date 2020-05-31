cmake_minimum_required(VERSION 3.0.0)
project(servers VERSION 0.1.0)

include(CTest)
enable_testing()

aux_source_directory(. SOURCE_DIR)
add_executable(servers ${SOURCE_DIR})

target_link_libraries(servers mysqlclient pthread crypt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
