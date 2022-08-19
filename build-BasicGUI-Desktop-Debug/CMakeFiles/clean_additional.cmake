# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BasicGUI_autogen"
  "CMakeFiles\\BasicGUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BasicGUI_autogen.dir\\ParseCache.txt"
  )
endif()
