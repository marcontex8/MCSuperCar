#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <iostream>

#include <string>
#include <vector>
#include <queue>

#include <fstream>


#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <ctime>

class Diagnostics {
public:
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

	Diagnostics();
	~Diagnostics();
	void log(std::string logMessage, Topic topic = Topic::Simulation, Verbosity verbosity = Verbosity::Debug);

	std::string readFromQueue(Topic topic);
private:
	typedef std::chrono::steady_clock::duration logger_time_duration;
	typedef std::tuple<logger_time_duration, Topic, Verbosity, std::string> LoggedElement;
	const std::chrono::steady_clock::time_point initial_time;

	std::atomic<bool> terminate_flag = false;
	std::future<bool> thread_terminated;

	void openFileStream();
	void closeFileStream();
	
	void processMessages();
	
	void writeToFile(LoggedElement log);
	void addToVector(LoggedElement log);
	std::string topic_toString(Topic topic);
	std::string verbosity_toString(Verbosity verbosity);
	std::string logger_time_to_string(logger_time_duration time);
	std::string logFolder = R"(D:\WorkSpace\MCSuperCar\logs\)";

	std::mutex logMutex;

	std::queue<LoggedElement> logQueue;
	std::condition_variable logCond;


	std::queue<std::string> simulationLogs;
	std::queue<std::string> guiLogs;
	std::queue<std::string> viewerLogs;

	std::mutex simulationLogMutex;
	std::mutex guiLogMutex;
	std::mutex viewerLogMutex;

	std::ofstream fileStream;
};

#endif