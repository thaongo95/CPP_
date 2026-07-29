cmake_minimum_required(VERSION 3.10)


project(GEO_STITCHER)

add_subdirectory(sources)

add_executable(App main.cpp)

target_link_libraries(App PRIVATE ${OpenCV_LIBS}
			  PRIVATE SOURCES)
