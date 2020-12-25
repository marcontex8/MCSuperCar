set(MCSC_MODULE_SIMULATOR_INCLUDE "${MCSC_MODULE_SIMULATOR_DIR}/include")
set(MCSC_MODULE_SIMULATOR_SOURCE "${MCSC_MODULE_SIMULATOR_DIR}/source")

add_executable(simulator
	"${MCSC_MODULE_SIMULATOR_SOURCE}/main.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/carMotionDynamic.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/Logger.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulationManager.cpp")

target_include_directories(simulator PUBLIC ${MCSC_MODULE_SIMULATOR_INCLUDE})

target_link_libraries(simulator ${CMAKE_THREAD_LIBS_INIT} )