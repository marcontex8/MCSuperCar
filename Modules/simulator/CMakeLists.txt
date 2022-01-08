# DEFINITION OF PATHS AND SOURCE FILES

set(MCSC_MODULE_SIMULATOR_INCLUDE "${MCSC_MODULE_SIMULATOR_DIR}/include")
set(MCSC_MODULE_SIMULATOR_SOURCE "${MCSC_MODULE_SIMULATOR_DIR}/source")
set(MCSC_MODULE_SIMULATOR_TESTS "${MCSC_MODULE_SIMULATOR_DIR}/tests")


set(SIMULATOR_SOURCE_FILES 
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulationElement.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulationElement_Car.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulatedWorld.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulationController.cpp"
	"${MCSC_MODULE_SIMULATOR_SOURCE}/SimulationManager.cpp")




# GENERATION OF LIBRARY SIMULATOR

add_library(Simulator ${SIMULATOR_SOURCE_FILES})

target_include_directories(Simulator PUBLIC ${MCSC_MODULE_SIMULATOR_INCLUDE})

target_link_libraries(Simulator ${CMAKE_THREAD_LIBS_INIT}
								Logger)


# CODE UNIT TESTING

enable_testing()

add_executable(SimulatorTester	"${MCSC_MODULE_SIMULATOR_TESTS}/SimulatedWorldTests.cpp"
								${SIMULATOR_SOURCE_FILES} )

target_include_directories(SimulatorTester PUBLIC	${MCSC_MODULE_SIMULATOR_INCLUDE}
													"${MCSC_EXTERNAL_DIR}/gtests/googletest/include")

target_link_libraries(SimulatorTester	${CMAKE_THREAD_LIBS_INIT} 
										Logger
										GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(SimulatorTester)
