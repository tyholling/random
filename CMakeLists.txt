cmake_minimum_required(VERSION 3.31)
project(hello LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -O3")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS Off)

add_executable(random main.cpp)
add_executable(test test.cpp)

target_link_libraries(random)
target_link_libraries(test)
