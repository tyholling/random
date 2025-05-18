cmake_minimum_required(VERSION 3.31)
project(hello LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -O3")

add_executable(random main.cpp)

target_link_libraries(random)
