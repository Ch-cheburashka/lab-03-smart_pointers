cmake_minimum_required(VERSION 3.0.0)

project(smart_pointers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_options(smart_pointers PRIVATE -Wall -Wextra -pedantic -Werror)

add_executable(smart_pointers main.cpp)