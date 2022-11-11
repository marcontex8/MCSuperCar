#include <QApplication>


#include "SuperCarWindow.h"
#include "Diagnostics.h"
#include "SimulationManager.h"
#include "WorldViewer_Manager.h"
#include "DiagnosticsWindow.h"

extern Diagnostics diagnostics = Diagnostics();

int main(int argc, char *argv[])
{
	std::locale::global(std::locale(""));
	std::cout << "main.cpp: started" << std::endl;
	diagnostics.log("main.cpp: started", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

	//INITIALIZING SIMULATOR
	auto world = std::make_shared<simulation::SimulatedWorld>();
	diagnostics.log("Created Simulated World", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
	simulation::SimulationManager simulationManager(world);
	diagnostics.log("Created Simulation Manager", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);


	//INITIALIZING WORLD VIEWER
	WorldViewerManager viewerManager(world);
	diagnostics.log("Created Viewer Manager", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
	viewerManager.initializeWorldView();

	// INITIALIZING GUI
	QApplication a(argc, argv);
	
	SuperCarWindow mainWindow(&simulationManager, &viewerManager);
	mainWindow.move(0, 0);
	mainWindow.show();


	return a.exec();
}
