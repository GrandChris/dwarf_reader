#
# Copyright (C) 2020 Assured Information Security, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Add Test
#
# Adds a test case given a name. Note that this will disable C++ access
# controls, assisting in unit testing.
#
# NAME: The name of the test case to add
#
macro(ut_add_test NAME)

    file(RELATIVE_PATH REL_NAME ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
    file(TO_CMAKE_PATH "${REL_NAME}" REL_NAME_UNMODIFIED)
    string(REPLACE "/" "_" REL_NAME ${REL_NAME_UNMODIFIED})
    string(REPLACE " " "_" REL_NAME ${REL_NAME})

    message(${NAME}.cpp)

    add_executable(${REL_NAME}_${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}.cpp)

    target_include_directories(${REL_NAME}_${NAME} PRIVATE)

    target_link_libraries(${REL_NAME}_${NAME} PRIVATE dwarf_reader)

    add_test(${REL_NAME}_${NAME} ${REL_NAME}_${NAME})

    add_custom_target(
        unittest_${REL_NAME}_${NAME}
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${REL_NAME_UNMODIFIED} ./${REL_NAME}_${NAME}
    )

endmacro(ut_add_test)
