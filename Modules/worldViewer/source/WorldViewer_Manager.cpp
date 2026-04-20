#include "WorldViewer_Manager.h"

#include<iostream>
#include "Diagnostics.h"

extern Diagnostics diagnostics;
;

WorldViewerManager::WorldViewerManager(std::shared_ptr<simulation::SimulatedWorld>& world):world(world) {
	int initResult = glfwInit();
	//initialize window
	if (initResult == GLFW_FALSE) {
		diagnostics.log("Failed to init glfw.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
		//throw WindowGenerationException();
	}
	diagnostics.log("GLFW initialized", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);

}

void WorldViewerManager::initializeWorldView() {
	terminationFlag = false;

	std::thread viewerThread(
		[this]() {
			std::promise<bool> promise;
			this->terminationResult = promise.get_future();
			{
				WorldViewer worldViewer(&terminationFlag, world);
				worldViewer.runView();
			}
			promise.set_value(true);
			diagnostics.log("Viewer thread terminated.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
			std::cout << "Viewer thread terminated." << std::endl;
		}
	);
	viewerThread.detach();
}

void WorldViewerManager::terminateWorldView() {
	diagnostics.log("Sending termination signal to viwer thread...", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
	std::cout << "Sending termination signal to viwer thread..." << std::endl;
	terminationFlag = true;
	try {
		terminationResult.wait();
		if (terminationResult.get()) {
			diagnostics.log("Viewer thread termiated correctly.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
			std::cout << "Viewer thread termiated correctly." << std::endl;
		}
	}
	catch (std::future_error e) {
		diagnostics.log("Viewer thread termination incorrect.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
		std::cout << "Viewer thread termination incorrect." << std::endl;
	}
}


WorldViewerManager::~WorldViewerManager() {
	diagnostics.log("Viewer Manager destructor called.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
	std::cout << "Viewer Manager destructor called." << std::endl;
	terminateWorldView();
	glfwTerminate();

}
