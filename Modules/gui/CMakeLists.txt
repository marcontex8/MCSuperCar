set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Required for Qt 
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
# set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "DEBUG")

set(PROJECT_SOURCES
        ${MCSC_MODULE_GUI_DIR}/source/main.cpp
        ${MCSC_MODULE_GUI_DIR}/source/supercar_gui.cpp
        ${MCSC_MODULE_GUI_DIR}/include/supercar_gui.h
        ${MCSC_MODULE_GUI_DIR}/ui/supercar_gui.ui
 "source/SimulationElementListModel.cpp" "include/SimulationElementListModel.h")

set(CMAKE_AUTOUIC_SEARCH_PATHS ${MCSC_MODULE_GUI_DIR}/ui/)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MCSuperCar_GUI    ${PROJECT_SOURCES})
else()
    add_executable(MCSuperCar_GUI   ${PROJECT_SOURCES})
endif()


target_include_directories(MCSuperCar_GUI   PUBLIC
            "${MCSC_MODULE_GUI_DIR}/include"
             ${MCSC_MODULE_SIMULATOR_INCLUDE})

target_link_libraries(MCSuperCar_GUI PRIVATE
                Qt${QT_VERSION_MAJOR}::Widgets
                Simulator)

# TODO: Aggiungere i test e, se necessario, installare le destinazioni.
