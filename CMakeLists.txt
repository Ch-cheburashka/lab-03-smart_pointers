cmake_minimum_required(VERSION 3.0.0)

project(smart_pointers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(shared_ptr INTERFACE)
add_library(unique_ptr INTERFACE)

target_include_directories(
        shared_ptr INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(
        unique_ptr INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

#target_compile_options(shared_ptr PRIVATE -Wall -Wextra -pedantic -Werror)
#target_compile_options(unique_ptr PRIVATE -Wall -Wextra -pedantic -Werror)

add_executable(cli cli/main.cpp)

target_link_libraries(cli shared_ptr)
target_link_libraries(cli unique_ptr)