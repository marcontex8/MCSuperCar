cmake_minimum_required (VERSION 3.8)

project (MCSuperCar VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Threads	REQUIRED)
find_package(OpenGL		REQUIRED)





# DEFINE PROJECT DIRECTORIES VARIABLES

# Define Project Directories
set(MCSC_MODULES_DIR "${PROJECT_SOURCE_DIR}/Modules")
message(STATUS "MCSC | modules dir: ${MCSC_MODULES_DIR}")

#Define External Directory
set(MCSC_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/External")
message(STATUS "MCSC | external dir: ${MCSC_EXTERNAL_DIR}")





# ADD EXTERNAL CODE

# glfw
add_subdirectory("${MCSC_EXTERNAL_DIR}/glfw")
include_directories("${MCSC_EXTERNAL_DIR}/glfw/include")

# glad
set(GLAD_C "${MCSC_EXTERNAL_DIR}/glad/src/glad.c")
include_directories("${MCSC_EXTERNAL_DIR}/glad/include")

# stb
include_directories("${MCSC_EXTERNAL_DIR}/stb")



# ADD MODULES DIRECTORIES
add_subdirectory (${MCSC_MODULES_DIR})