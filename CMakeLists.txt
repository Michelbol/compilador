cmake_minimum_required(VERSION 3.15)

project(calculator_laguage)

find_package(BISON)
find_package(FLEX)

add_definitions(-D_DEBUG -D_STDC_CONSTANT_MACROS -DSTDC_FORMAT_MACROS -D_STDC_LIMIT_MACROS)

BISON_TARGET(MyParser front_end.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
FLEX_TARGET(MyScanner front_end.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.c)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(calclang ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS} binary_tree.c variables.c helpers.c)