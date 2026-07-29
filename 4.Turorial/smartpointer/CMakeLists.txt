cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RUN VERSION 1.0)

add_subdirectory(lib)

add_executable(RUN shared_pointer.cpp)

target_link_libraries(RUN PUBLIC SmartPtr)

