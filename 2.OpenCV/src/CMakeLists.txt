


add_library(Functions image_functions.cpp video_functions.cpp app_tools.cpp interactive_image.cpp interactive_video.cpp document_scan.cpp)

target_include_directories(Functions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
find_package(OpenCV REQUIRED)
target_link_libraries(Functions PUBLIC ${OpenCV_LIBS})
