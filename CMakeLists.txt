cmake_minimum_required(VERSION 3.10)
project(layout_design)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES "src/*.cpp")
include_directories(include)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
set(SANITIZER -fsanitize=address,undefined -fno-omit-frame-pointer)
target_compile_options(${PROJECT_NAME} PRIVATE ${SANITIZER})
target_link_options(${PROJECT_NAME} PRIVATE ${SANITIZER})