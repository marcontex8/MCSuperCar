include_directories("${MCSC_EXTERNAL_DIR}/glad/include")

set(MCSC_MODULE_WORLD_VIEWER_INCLUDE "${MCSC_MODULE_WORLD_VIEWER_DIR}/include")
set(MCSC_MODULE_WORLD_VIEWER_SOURCE "${MCSC_MODULE_WORLD_VIEWER_DIR}/source")

#add_library(WorldViewer
#	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/world_viewer.cpp")

#target_include_directories(WorldViewer PUBLIC ${MCSC_MODULE_WORLD_VIEWER_INCLUDE})

#target_link_libraries(WorldViewer glfw ${GLFW_LIBRARIES})

add_executable(worldViewer 
					"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/world_viewer.cpp"
					"${MCSC_EXTERNAL_DIR}/glad/src/glad.c")

target_link_libraries(worldViewer glfw ${GLFW_LIBRARIES})
