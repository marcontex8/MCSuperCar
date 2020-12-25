cmake_minimum_required (VERSION 3.8)

project (MCSuperCar VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( Threads )

# Define Project Directories
set(MCSC_MODULES_DIR "${PROJECT_SOURCE_DIR}/Modules")
message(STATUS "MCSC | modules dir: ${MCSC_MODULES_DIR}")

# Add modules directory
add_subdirectory (${MCSC_MODULES_DIR})


