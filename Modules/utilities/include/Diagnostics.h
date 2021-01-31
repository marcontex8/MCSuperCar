#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <iostream>

#include <string>
#include <vector>
#include <queue>

#include <fstream>


#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>


class Diagnostics {
public:
	Diagnostics();
	~Diagnostics();

	enum class Topic {
		Simulation,
		Gui,
		Viewer
	};

	enum class Verbosity {
		Debug,
		Warning,
		Error
	};
	typedef std::chrono::steady_clock::duration logger_time_duration;
	typedef std::tuple<logger_time_duration, Topic, Verbosity, std::string> LoggedElement;
	const std::chrono::steady_clock::time_point initial_time;

	void initializeFileStream();
	void log(std::string logMessage, Topic topic = Topic::Simulation, Verbosity verbosity = Verbosity::Debug);
	void processMessages();
	void writeToFile(LoggedElement log);
	void addToVector(LoggedElement log);
	std::string topic_toString(Topic topic);
	std::string verbosity_toString(Verbosity verbosity);
	std::string logger_time_to_string(logger_time_duration time);
private:
	std::string logFolder = R"(D:\WorkSpace\MCSuperCar\logs\)";

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
};

#endif