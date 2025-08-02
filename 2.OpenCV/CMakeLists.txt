cmake_minimum_required(VERSION 3.15)


project(Test)
#find_package(OpenCV REQUIRED)

set(RESOURCE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(RESOURCE_DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}/assets)

add_subdirectory(src)

add_executable(App main.cpp)


add_custom_command(
	TARGET App POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${RESOURCE_SOURCE_DIR}"
		"${RESOURCE_DEST_DIR}"	
)


target_link_libraries(App PRIVATE ${OpenCV_LIBS}
	                  PRIVATE Functions)

