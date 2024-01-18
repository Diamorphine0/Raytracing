# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles/Ray-tracing_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Ray-tracing_autogen.dir/ParseCache.txt"
  "Ray-tracing_autogen"
  )
endif()
