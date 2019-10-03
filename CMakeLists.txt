cmake_minimum_required( VERSION 3.10 )

project( CodingPractice VERSION 0.1
                        LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

add_subdirectory( "extern/googletest" )
enable_testing()

macro(add_exercise TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
endmacro()

add_subdirectory( Array )
add_subdirectory( DynamicProgramming )
add_subdirectory( Stack )
