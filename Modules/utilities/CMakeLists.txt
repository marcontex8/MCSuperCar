set(MCSC_MODULE_UTILITIES_INCLUDE "${MCSC_MODULE_UTILITIES_DIR}/include")
set(MCSC_MODULE_UTILITIES_SOURCE "${MCSC_MODULE_UTILITIES_DIR}/source")

add_library(Logger
	"${MCSC_MODULE_UTILITIES_SOURCE}/Diagnostics.cpp")

target_include_directories(Logger PUBLIC ${MCSC_MODULE_UTILITIES_INCLUDE})

target_link_libraries(Logger ${CMAKE_THREAD_LIBS_INIT}
								)


add_executable(openglTest 
							${GLAD_C}
							"${MCSC_MODULE_UTILITIES_SOURCE}/OpenGL_test.cpp")


target_link_libraries(openglTest
							glfw
							${GLFW_LIBRARIES}
)