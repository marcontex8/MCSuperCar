#include <iostream>

#include <QApplication>
#include <QAbstractItemModel>
#include <QListView>

#include "supercar_gui.h"
#include "ui_supercar_gui.h"

#include "SimulationElementListModel.h"
#include "Logger.h"
#include "SimulationManager.h"
#include "simulationSettings.h"

int main(int argc, char *argv[])
{
	//INITIALIZING SIMULATOR

	//Logger simulationLogger;
	//simulationLogger.initialize();

	simulation::SimulatedWorld world;
	simulation::SimulationElement element1;
	simulation::SimulationElement element2;
	simulation::SimulationElement element3;
	std::cout << "created elements" << std::endl;

	world.addElement(element1);
	world.addElement(element2);
	world.addElement(element3);
	std::cout << "added elements" << std::endl;

	simulation::SimulationManager simulationManager(&world);
	std::cout << "created manager" << std::endl;

	simulationManager.simulationController.setSimulationIntervalMillis(20);
	std::cout << "set interval" << std::endl;

	simulationManager.beginSimulation();
	std::cout << "simulation running" << std::endl;

    // Unindented for quoting purposes:
    std::vector<std::string> numbers{ "One","Two","Three","Four","Five" };



	// INITIALIZING GUI
	QApplication a(argc, argv);
	SuperCarMain_GUI mainWindow;
	Ui::SuperCarMain_GUI ui;
	ui.setupUi(&mainWindow);

    QAbstractItemModel* model = new SimulationElementListModel(numbers);

    ui.elements_list_view->setModel(model);
	mainWindow.show();
    return a.exec();



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
