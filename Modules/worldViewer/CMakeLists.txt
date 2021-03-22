set(MCSC_MODULE_WORLD_VIEWER_INCLUDE "${MCSC_MODULE_WORLD_VIEWER_DIR}/include")
set(MCSC_MODULE_WORLD_VIEWER_SOURCE "${MCSC_MODULE_WORLD_VIEWER_DIR}/source")

add_library(ViewerManager
	${GLAD_C}
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/WorldViewer_Manager.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/WorldViewer.cpp"

	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/Scene.cpp"
	
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/Shaders.cpp"
		
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/Definitions_CarPack001.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/Drawer_CarPack001.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/Factory_CarPack001.cpp"
	
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/Factory_SimpleElements.cpp"
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/Drawer_Box.cpp"
	
	"${MCSC_MODULE_WORLD_VIEWER_SOURCE}/Drawer_SimpleTerrain.cpp"
	)


target_include_directories(ViewerManager PUBLIC ${MCSC_MODULE_WORLD_VIEWER_INCLUDE})

target_link_libraries(ViewerManager
							glfw
							
							assimp::assimp
							${GLFW_LIBRARIES}
							Simulator
							Logger)
