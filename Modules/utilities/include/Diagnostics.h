#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <iostream>

#include <string>
#include <vector>
#include <queue>
#include <map>

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

	typedef std::chrono::steady_clock::duration diagnostics_time;
	typedef std::tuple<diagnostics_time, Topic, Verbosity, std::string> LoggedElement;
	typedef std::tuple<diagnostics_time, std::string> MonitorElementValue;
	typedef std::pair<std::string, MonitorElementValue> MonitorElement;


	Diagnostics();
	~Diagnostics();
	void log(std::string logMessage, Topic topic = Topic::Simulation, Verbosity verbosity = Verbosity::Debug);
	void monitor(std::string key, std::string value);
	std::string getMonitorString();
	std::string getLogString(Topic topic);
private:

	const std::chrono::steady_clock::time_point initial_time;

	std::atomic<bool> terminate_flag = false;
	std::future<bool> log_thread_terminated;
	std::future<bool> monitor_thread_terminated;

	void openFileStream();
	void closeFileStream();
	
	void processLogMessages();
	void processMonitorMessage();
	
	void writeToFile(LoggedElement log);
	
	void addToMonitorMap(std::string key, MonitorElementValue value);
	void addToLogQueue(LoggedElement element);

	std::string topic_toString(Topic topic);
	std::string verbosity_toString(Verbosity verbosity);
	std::string logger_time_to_string(diagnostics_time time);
	std::string logFolder = R"(D:\WorkSpace\MCSuperCar\logs\)";

	// Input log queue
	std::mutex logMutex;
	std::queue<LoggedElement> logQueue;
	std::condition_variable logCond;

	// Input monitor queue
	std::mutex monitorInputMutex;
	std::queue<MonitorElement> monitorInputQueue;
	std::condition_variable monitorInputCond;

	// Output logs queues
	std::mutex guiLogMutex;
	std::queue<LoggedElement> guiLogQueue;
	std::mutex simulationLogMutex;
	std::queue<LoggedElement> simulationLogQueue;
	std::mutex viewerLogMutex;
	std::queue<LoggedElement> viewerLogQueue;

	// Output monitor 
	std::mutex monitorOutputMutex;
	std::map<std::string, MonitorElementValue> monitorOutput;

	std::ofstream fileStream;
};

#endif