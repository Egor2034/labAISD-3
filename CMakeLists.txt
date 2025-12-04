# CMakeList.txt : CMake project for lab3, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (lab3 "lab3.cpp" "functions.h")
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab3 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
