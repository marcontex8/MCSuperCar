﻿cmake_minimum_required (VERSION 3.8)

project (MCSuperCar VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

find_package(Threads	REQUIRED)
find_package(OpenGL		REQUIRED)
# DEFINE PROJECT DIRECTORIES VARIABLES

# Define Project Directories
set(MCSC_MODULES_DIR "${PROJECT_SOURCE_DIR}/Modules")
message(STATUS "MCSC | modules dir: ${MCSC_MODULES_DIR}")

#Define External Directory
set(MCSC_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/External")
message(STATUS "MCSC | external dir: ${MCSC_EXTERNAL_DIR}")

#Define Tests Directory
set(MCSC_TESTS_DIR "${PROJECT_SOURCE_DIR}/Tests")
message(STATUS "MCSC | tests dir: ${MCSC_TESTS_DIR}")


# ADD EXTERNAL CODE

# glfw
add_subdirectory("${MCSC_EXTERNAL_DIR}/glfw")
include_directories("${MCSC_EXTERNAL_DIR}/glfw/include")

# glad
set(GLAD_C "${MCSC_EXTERNAL_DIR}/glad/src/glad.c")
include_directories("${MCSC_EXTERNAL_DIR}/glad/include")

# stb
include_directories("${MCSC_EXTERNAL_DIR}/stb")

# glm
include_directories("${MCSC_EXTERNAL_DIR}/glm")

# eigen
include_directories("${MCSC_EXTERNAL_DIR}/eigen")

# assimp
add_subdirectory("${MCSC_EXTERNAL_DIR}/assimp")

# gtests
add_subdirectory("${MCSC_EXTERNAL_DIR}/gtests/")


# ADD MODULES DIRECTORIES
add_subdirectory (${MCSC_MODULES_DIR})



