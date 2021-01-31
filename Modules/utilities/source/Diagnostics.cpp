#include "Diagnostics.h"
#include <cmath>
#include <type_traits>
#include <cstdint>

Diagnostics::Diagnostics() : initial_time( std::chrono::steady_clock::now() )
{
	std::cout << "Logger constructor called." << std::endl;
	initializeFileStream();
}

Diagnostics::~Diagnostics(){
	std::cout << "Logger destructor called." << std::endl;
	// get current system clock time
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string string_time(30, '\0');
	std::strftime(&string_time[0], string_time.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - initial_time;
	writeToFile(LoggedElement(time, Topic::Simulation, Verbosity::Debug, "Logging ended at: "+ string_time));
	fileStream.close();
}

void Diagnostics::initializeFileStream() {
	std::lock_guard<std::mutex> lk(logMutex);

	// get current system clock time
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string string_time(30, '\0');
	std::strftime(&string_time[0], string_time.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

	char nameFile_time[20];
	std::strftime(&nameFile_time[0], 20, "%Y%m%d_%H%M_%S", std::localtime(&now));
	std::string str_nameFile_time(nameFile_time);
	std::string logFile = logFolder + "log_" + str_nameFile_time +".csv";

	fileStream.open(logFile, std::ofstream::out | std::ofstream::app);


	std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - initial_time;
	writeToFile(LoggedElement(time, Topic::Simulation, Verbosity::Debug,
		"New log started at (tyme system) "+string_time+" in file "+logFile));

	loggerThread = std::thread([this]() {processMessages(); });
	loggerThread.detach();
	

	if (fileStream.is_open()) {
		std::cout << "Logger file "+ logFile +" correctly initialized" << std::endl;
	}
	else {
		std::cout << "Logger file " + logFile + " initialization failed" << std::endl;
	}
}

void Diagnostics::log(std::string logMessage, Topic topic, Verbosity verbosity) {
	std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - initial_time;
	LoggedElement newLog(time, topic, verbosity, logMessage);
	{
		std::lock_guard<std::mutex> lk(logMutex);
		logQueue.push(newLog);
	}
	logCond.notify_one();
}

void Diagnostics::processMessages() {
	while (true) {
		std::unique_lock<std::mutex> lk(logMutex);
		
		logCond.wait(lk, [this]() {return !logQueue.empty(); });
		LoggedElement newLog = logQueue.front();
		logQueue.pop();
		lk.unlock();
		writeToFile(newLog);
		addToVector(newLog);
	}
}

void Diagnostics::addToVector(LoggedElement log) {
	auto [time, topic, verbosity, message] = log;
	std::string formattedTime = Diagnostics::logger_time_to_string(time);
	std::string stringLog = formattedTime + "-" + verbosity_toString(verbosity) + " - " + message;
	if (topic == Diagnostics::Topic::Simulation) {
		std::lock_guard<std::mutex> lkSim(simulationLogMutex);
		simulationLogs.push_back(stringLog);
	}
	else if (topic == Diagnostics::Topic::Gui) {
		std::lock_guard<std::mutex> lkGui(guiLogMutex);
		guiLogs.push_back(stringLog);
	} 
	else if (topic == Diagnostics::Topic::Viewer) {
		std::lock_guard<std::mutex> lkViewer(viewerLogMutex);
		viewerLogs.push_back(stringLog);
	}
}

void Diagnostics::writeToFile(LoggedElement log) {
	auto [time, topic, verbosity, message] = log;
	using namespace std::chrono_literals;
	static std::chrono::nanoseconds lastTime = 0us;
	auto elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
	std::string timeGap = std::to_string(((double)(elapsed_nanoseconds-lastTime).count()) / 1000 / 1000);
	std::string formattedTime = Diagnostics::logger_time_to_string(time);
	std::string stringLog = formattedTime + ";" + timeGap + ";" + verbosity_toString(verbosity) + " ; " + topic_toString(topic) + " ; " + message;
	if (fileStream.is_open()) {
		fileStream << stringLog << std::endl;
		lastTime = elapsed_nanoseconds;
	}
}

std::string Diagnostics::topic_toString(Topic topic) {
		switch (topic)
		{
			case Diagnostics::Topic::Simulation:
				return std::string("Simulation");
			case Diagnostics::Topic::Gui:
				return std::string("Gui");
			case Diagnostics::Topic::Viewer:
				return std::string("Viewer");
			default:
				return std::string("");
		}
}

std::string Diagnostics::verbosity_toString(Verbosity verbosity) {
	switch (verbosity)
	{
		case Diagnostics::Verbosity::Debug:
			return std::string("DEBUG");
		case Diagnostics::Verbosity::Warning:
			return std::string("WARNING");
		case Diagnostics::Verbosity::Error:
			return std::string("ERROR");
		default:
			return std::string("");
	}
}

std::string Diagnostics::logger_time_to_string(logger_time_duration time) {
	/*
	* USE THIS TO OBTAIN format m:s:ms:us:ns
	* 
	auto elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();
	auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
	auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count();
	auto elapsed_minutes = std::chrono::duration_cast<std::chrono::minutes>(time).count();
	
	auto m = elapsed_minutes;
	auto s = elapsed_seconds - (long long)elapsed_minutes * 60;
	auto ms = elapsed_milliseconds - elapsed_seconds * 1000;
	auto us = elapsed_microseconds - elapsed_milliseconds * 1000;
	auto ns = elapsed_nanoseconds - elapsed_microseconds * 1000;


	std::string formattedTime;
	formattedTime = std::to_string(m) + ":" + std::to_string(s) + ":" + std::to_string(ms) + ":" + std::to_string(us) + ":" + std::to_string(ns);
	return formattedTime;
	*/
	auto elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();
	double milliseconds_with_decimals = ((double)elapsed_nanoseconds) / 1000 / 1000;
	return std::string(std::to_string(milliseconds_with_decimals));
}
