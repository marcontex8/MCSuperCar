#TODO: check the availability of module?

set(MCSC_MODULE_SIMULATOR_DIR "${MCSC_MODULES_DIR}/simulator")
set(MCSC_MODULE_WORLD_VIEWER_DIR "${MCSC_MODULES_DIR}/world_viewer")
set(MCSC_MODULE_GUI_DIR "${MCSC_MODULES_DIR}/gui")


message(STATUS "MCSC | simulator dir: ${MCSC_MODULE_SIMULATOR_DIR}")
message(STATUS "MCSC | world viewer dir: ${MCSC_MODULE_WORLD_VIEWER_DIR}")
message(STATUS "MCSC | gui dir: ${MCSC_MODULE_GUI_DIR}")


add_subdirectory (${MCSC_MODULE_SIMULATOR_DIR})
add_subdirectory (${MCSC_MODULE_WORLD_VIEWER_DIR})
add_subdirectory (${MCSC_MODULE_GUI_DIR})

