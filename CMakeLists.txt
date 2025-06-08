cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "my_cat")
set(PROJECT_VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(fmt REQUIRED)
find_package(CLI11 REQUIRED)
find_package(Catch2 REQUIRED)

add_subdirectory(app)
add_subdirectory(tests)
