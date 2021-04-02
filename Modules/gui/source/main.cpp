#include <QApplication>


#include "supercar_gui.h"
#include "Diagnostics.h"
#include "SimulationManager.h"
#include "WorldViewer_Manager.h"
#include "DiagnosticsWindow.h"

extern Diagnostics diagnostics = Diagnostics();

int main(int argc, char *argv[])
{
	std::locale::global(std::locale(""));
	std::cout << "main.cpp: started" << std::endl;
	//INITIALIZING SIMULATOR

	diagnostics.log("iniziato!!!", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);

	simulation::SimulatedWorld world;
	simulation::SimulationManager simulationManager(&world);
	std::cout << "created manager" << std::endl;

	simulationManager.simulationController.setSimulationIntervalMillis(20);
	std::cout << "set interval" << std::endl;



	//INITIALIZING WORLD VIEWER
	WorldViewerManager viewerManager(&world);
	viewerManager.initializeWorldView();

	// INITIALIZING GUI
	QApplication a(argc, argv);
	
	SuperCarMain_GUI mainWindow(&simulationManager, &viewerManager);
	mainWindow.move(0, 0);
	mainWindow.show();


	return a.exec();
}
