cmake_minimum_required (VERSION 3.8)

project (MCSuperCar VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( Threads )

find_package(OpenGL REQUIRED)

# Define Project Directories
set(MCSC_MODULES_DIR "${PROJECT_SOURCE_DIR}/Modules")
message(STATUS "MCSC | modules dir: ${MCSC_MODULES_DIR}")

#Define External Directory
set(MCSC_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/External")
message(STATUS "MCSC | external dir: ${MCSC_EXTERNAL_DIR}")

# Add external directories
add_subdirectory("${MCSC_EXTERNAL_DIR}/glfw")
include_directories("${MCSC_EXTERNAL_DIR}/glfw/include")

# Add modules directory
add_subdirectory (${MCSC_MODULES_DIR})