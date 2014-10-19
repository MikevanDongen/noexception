cmake_minimum_required(VERSION 2.8.4)
project(noexception C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic")
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
enable_testing()

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${LIBRARY_OUTPUT_PATH})

include_directories("include/")

add_library(noexception SHARED "src/noexception.c")

add_executable(noexception_test tests/test.c)
target_link_libraries(noexception_test noexception check)
add_test(test ${CMAKE_CURRENT_BINARY_DIR}/noexception_test)