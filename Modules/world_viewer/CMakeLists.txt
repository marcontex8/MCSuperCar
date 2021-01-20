set(MCSC_MODULE_WORLD_VIEWER_INCLUDE "${MCSC_MODULE_WORLD_VIEWER_DIR}/include")
set(MCSC_MODULE_WORLD_VIEWER_SOURCE "${MCSC_MODULE_WORLD_VIEWER_DIR}/source")

add_library(ViewerManager
	${GLAD_C}
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/ViewerManager.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/world_viewer.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/ElementDrawer.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/ElementOpenGLDefinitions.cpp")

target_include_directories(ViewerManager PUBLIC ${MCSC_MODULE_WORLD_VIEWER_INCLUDE})

target_link_libraries(ViewerManager
							glfw
							${GLFW_LIBRARIES}
							Simulator	)

add_executable(test
${GLAD_C}
"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/test.cpp"
)

target_link_libraries(test
							glfw
							${GLFW_LIBRARIES}
							)

#add_executable(worldViewer 
#					"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/world_viewer.cpp"
#					${GLAD_C})

#target_link_libraries(worldViewer glfw ${GLFW_LIBRARIES})