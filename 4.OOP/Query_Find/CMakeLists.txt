cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Query)
file(GLOB SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/finder.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/result.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/query.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/and_query.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/word_query.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/not_query.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/or_query.cpp)

add_executable(BookShop main.cpp ${SOURCE_FILE})

target_link_directories(BookShop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
                      
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
