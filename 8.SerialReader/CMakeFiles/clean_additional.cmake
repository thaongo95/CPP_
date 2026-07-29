# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\appserial_reader_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appserial_reader_autogen.dir\\ParseCache.txt"
  "appserial_reader_autogen"
  )
endif()
