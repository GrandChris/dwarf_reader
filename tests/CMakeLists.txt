#
# @file:   CMakeLists.txt
# @author: GrandChris
# @date:   2021-12-31
# @note:   Modified version from https://github.com/Bareflank/bsl
#



include(${CMAKE_SOURCE_DIR}/cmake/function/ut_add_test.cmake)

add_subdirectory(pei)
add_subdirectory(dwarf)
add_subdirectory(example_program)
