set(MCSC_MODULE_WORLD_VIEWER_INCLUDE "${MCSC_MODULE_WORLD_VIEWER_DIR}/include")
set(MCSC_MODULE_WORLD_VIEWER_SOURCE "${MCSC_MODULE_WORLD_VIEWER_DIR}/source")

add_library(ViewerManager
	${GLAD_C}
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/ViewerManager.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/world_viewer.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/DrawersFactory.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/BoxDrawer.cpp"

)


target_include_directories(ViewerManager PUBLIC ${MCSC_MODULE_WORLD_VIEWER_INCLUDE})

target_link_libraries(ViewerManager
							glfw
							${GLFW_LIBRARIES}
							Simulator
							Logger)