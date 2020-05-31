cmake_minimum_required(VERSION 3.0.0)
project(client VERSION 0.1.3)

include(CTest)
enable_testing()

aux_source_directory(. SOURCE_DIR)
add_executable(client ${SOURCE_DIR})

target_link_libraries(client pthread crypt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
