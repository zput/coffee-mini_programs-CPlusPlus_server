cmake_minimum_required(VERSION 2.6)
project(MiniProgram_http)

enable_testing()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(NOT CMAKE_STUB_FORMATTER)
    set(CMAKE_STUB_FORMATTER echo)
endif()

set(CXX_FLAGS
        -fno-omit-frame-pointer         # linux perf
        # -Wall
        # -Wextra
        # -Werror
        # -Wconversion
        # -Wno-unused-parameter
        # -Wold-style-cast
        # -Woverloaded-virtual
        # -Wpointer-arith
        # -Wshadow
        # -Wwrite-strings
        -std=c++17
        -march=native
        -rdynamic)
		
	   # string(  REPLACE   (match_string) (replace_string) (output variable) (input) [(input)...])

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

message(STATUS "MiniProgram_http project PROJECT_BINARY_DIR is ${PROJECT_BINARY_DIR} PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR} CMAKE_BUILD_NO_EXAMPLES is ${CMAKE_BUILD_NO_EXAMPLES} ")

include_directories(
         3rd/zxc_net
         ${PROJECT_SOURCE_DIR}
         ${PROJECT_BINARY_DIR}
		)

add_subdirectory(3rd/zxc_net)
add_subdirectory(MiniProgram_http)

if(NOT CMAKE_BUILD_NO_EXAMPLES_EXCEPT_MAIN_PROJECT)
    add_subdirectory(example)
endif()



