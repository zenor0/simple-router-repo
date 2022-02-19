cmake_minimum_required(VERSION 3.0.0)
project(simple-router VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options(-Wall -Wextra)

aux_source_directory(. DIR_SRCS)

add_executable(simple-router ${DIR_SRCS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
