#TODO: check the availability of module?

set(MCSC_MODULE_GUI_DIR "${MCSC_MODULES_DIR}/gui")
set(MCSC_MODULE_SIMULATOR_DIR "${MCSC_MODULES_DIR}/simulator")

message(STATUS "MCSC | gui dir: ${MCSC_MODULE_GUI_DIR}")
message(STATUS "MCSC | simulator dir: ${MCSC_MODULE_SIMULATOR_DIR}")

add_subdirectory (${MCSC_MODULE_GUI_DIR})
add_subdirectory (${MCSC_MODULE_SIMULATOR_DIR})

