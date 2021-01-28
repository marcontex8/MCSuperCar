set(MCSC_MODULE_SIMULATOR_INCLUDE "${MCSC_MODULE_SIMULATOR_DIR}/include")
set(MCSC_MODULE_SIMULATOR_SOURCE "${MCSC_MODULE_SIMULATOR_DIR}/source")

add_library(Simulator
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulationElement.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulatedWorld.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulationController.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulationManager.cpp")

target_include_directories(Simulator PUBLIC ${MCSC_MODULE_SIMULATOR_INCLUDE})

target_link_libraries(Simulator ${CMAKE_THREAD_LIBS_INIT}
								Logger)