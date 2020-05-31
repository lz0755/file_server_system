cmake_minimum_required(VERSION 3.0.0)
project(serverc VERSION 0.1.4)

include(CTest)
enable_testing()

aux_source_directory(. SOURCE_DIR)
add_executable(serverc ${SOURCE_DIR})

target_link_libraries(serverc pthread crypt mysqlclient)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
