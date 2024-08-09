cmake_minimum_required(VERSION 3.0.0)

project(include/smart_pointers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(smart_pointers INTERFACE)

target_include_directories(
        smart_pointers INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_executable(cli cli/main.cpp)
target_link_libraries(cli smart_pointers)