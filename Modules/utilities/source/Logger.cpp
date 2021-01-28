#include "Logger.h"

Logger::Logger() {
	std::cout << "Logger constructor called." << std::endl;
	initialize();
}

Logger::~Logger(){
	std::cout << "Logger destructor called." << std::endl;
	fileStream << "Logger destructor: closing log file." << std::endl;
	fileStream.close();
}

void Logger::initialize() {
	std::lock_guard<std::mutex> lk(logMutex);
	fileStream.open(logFile, std::ofstream::out | std::ofstream::app);
	loggerThread = std::thread([this]() {processMessages(); });
	loggerThread.detach();

	if (fileStream.is_open()) {
		fileStream << "New Log Started." << std::endl;
		std::cout << "Logger correctly initialized" << std::endl;
	}
	else {
		std::cout << "Logger initialization failed" << std::endl;
	}
}

void Logger::log(std::string logMessage, Topic topic, Verbosity verbosity) {
	LoggedElement newLog(topic, verbosity, logMessage);
	{
		std::lock_guard<std::mutex> lk(logMutex);
		logQueue.push(newLog);
	}
	logCond.notify_one();
}

void Logger::processMessages() {
	while (true) {
		std::cout << "New Log cycle " << std::endl;
		std::unique_lock<std::mutex> lk(logMutex);
		
		logCond.wait(lk, [this]() {return !logQueue.empty(); });
		LoggedElement newLog = logQueue.front();
		logQueue.pop();
		lk.unlock();
		writeToFile(newLog);
		addToVector(newLog);
	}
}

void Logger::addToVector(LoggedElement log) {
	auto [topic, verbosity, message] = log;
	std::string stringLog = verbosity_toString(verbosity) + " - " + message;
	if (topic == Logger::Topic::Simulation) {
		std::lock_guard<std::mutex> lkSim(simulationLogMutex);
		simulationLogs.push_back(stringLog);
	}
	else if (topic == Logger::Topic::Gui) {
		std::lock_guard<std::mutex> lkGui(guiLogMutex);
		guiLogs.push_back(stringLog);
	} 
	else if (topic == Logger::Topic::Viewer) {
		std::lock_guard<std::mutex> lkViewer(viewerLogMutex);
		viewerLogs.push_back(stringLog);
	}
}

void Logger::writeToFile(LoggedElement log) {
	auto [topic, verbosity, message] = log;
	std::string stringLog = verbosity_toString(verbosity) + " ; " + topic_toString(topic) + " ; " + message;
	if (fileStream.is_open()) {
		fileStream << stringLog << std::endl;
	}
}

std::string Logger::topic_toString(Topic topic) {
	switch (topic)
	{
		case Logger::Topic::Simulation:
			return std::string("Simulation");
		case Logger::Topic::Gui:
			return std::string("Gui");
		case Logger::Topic::Viewer:
			return std::string("Viewer");
		default:
			return std::string("");
	}
}

std::string Logger::verbosity_toString(Verbosity verbosity) {
	switch (verbosity)
	{
		case Logger::Verbosity::Debug:
			return std::string("DEBUG");
		case Logger::Verbosity::Warning:
			return std::string("WARNING");
		case Logger::Verbosity::Error:
			return std::string("ERROR");
		default:
			return "";
	}
}