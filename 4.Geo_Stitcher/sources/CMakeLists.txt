add_library(SOURCES utils.cpp stitching_images.cpp)

target_include_directories(SOURCES INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
find_package(OpenCV REQUIRED)
target_link_libraries(SOURCES PUBLIC ${OpenCV_LIBS})
