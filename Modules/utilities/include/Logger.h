#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <thread>
#include<iostream>

class Logger
{
public:
	enum class Topic{
		Simulation,
		Gui,
		Viewer
	};

	enum class Verbosity {
		Debug,
		Warning,
		Error
	};

	typedef std::tuple<Topic, Verbosity, std::string> LoggedElement;

private:
	std::string logFile = R"(D:\WorkSpace\MCSuperCar\logs\logs.csv)";

	std::thread loggerThread;

	std::mutex logMutex;
	std::queue<LoggedElement> logQueue;
	std::condition_variable logCond;

	std::vector<std::string> simulationLogs;
	std::vector<std::string> guiLogs;
	std::vector<std::string> viewerLogs;

	std::mutex simulationLogMutex;
	std::mutex guiLogMutex;
	std::mutex viewerLogMutex;
	
	std::ofstream fileStream;

public:
	Logger::Logger();
	Logger::~Logger();

	void initialize();
//	void Logger::log(std::string logMessage, Topic topic = Topic::Simulation, Verbosity verbosity = Verbosity::Debug);
	void Logger::log(std::string logMessage, Topic topic = Topic::Simulation, Verbosity verbosity = Verbosity::Debug);
	void processMessages();
	void writeToFile(LoggedElement log);
	void addToVector(LoggedElement log);
	std::string topic_toString(Topic topic);
	std::string verbosity_toString(Verbosity verbosity);
};
/*
class LoggerManager {
public:
	static Logger logger;
};
*/

#endif