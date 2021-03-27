#include <iostream>

#include "WorldViewer.h"


#include <QApplication>
#include <QAbstractItemModel>
#include <QListView>
#include <qpushbutton.h>

#include "supercar_gui.h"
#include "ui_supercar_gui.h"

#include "DiagnosticsWindow.h"
#include "ui_supercar_gui.h"

#include "Diagnostics.h"
#include "SimulationManager.h"
#include "simulationSettings.h"

#include "WorldViewer_Manager.h"

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
	
	SuperCarMain_GUI mainWindow(&simulationManager);
	mainWindow.move(0, 0);
	mainWindow.show();

	DiagnosticsWindow diagnosticWindow(&diagnostics);
	diagnosticWindow.move(mainWindow.width()+10, 0);
	diagnosticWindow.show();
	return a.exec();

	static QScreen* screen = QGuiApplication::screens()[0];

	QRect screenGeometry = screen->availableGeometry();
	int height = screenGeometry.height();
	int width = screenGeometry.width();
	//set to middle of screen
	// INITIALIZING TERMINAL UI
	/*
	bool done = false;
	while (!done) {
		std::cout << "nuovo ciclo" << std::endl;
		std::string input;
		// user input
		std::getline(std::cin, input);
		std::cout << input << std::endl;
		if (input == "q") {

			std::cout << "Simulation End required." << std::endl;
			simulationManager.endSimulation();
			while (!simulationManager.simulationEnded()) {
				std::cout << "waiting for simulation to end..." << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				continue;
			}
			done = true;
			input = "";
			break;
		}

		if (input == "p") {
			std::cout << "Simulation pause required." << std::endl;
			simulationManager.pauseSimulation();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			input = "";
			continue;
		}

		if (input == "r") {
			std::cout << "Simulation play required." << std::endl;
			simulationManager.playSimulation();
			input = "";
			continue;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
		*/
}
