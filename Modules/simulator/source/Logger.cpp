#include "Logger.h"
#include<iostream>
Logger::Logger() {

}

Logger::~Logger() {
	logFileStream.flush();
	std::cout << "closing logs" << std::endl;
	logFileStream.close();
}

void Logger::initialize() {
	logFileStream.open(fileName);
	if (logFileStream.is_open()) {
		std::cout << "logger initialized" << std::endl;
		logFileStream << "New Log Started." << std::endl;
	}
	else
	{
		std::cout << "logger initialization failed" << std::endl;
	}
}
void Logger::log(std::string logMessage) {
	//std::cout << logMessage << std::endl;
	logFileStream << logMessage << std::endl;
	logFileStream.flush();
}