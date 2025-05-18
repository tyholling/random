cmake_minimum_required(VERSION 3.31)
project(hello LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(hello main.cpp)

target_link_libraries(hello)
