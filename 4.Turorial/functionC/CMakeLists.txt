cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RUN VERSION 1.0)

file(GLOB SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/sources/frenchdeck.cpp)
add_executable(RUN main.cpp ${SOURCE})
target_include_directories(RUN PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



