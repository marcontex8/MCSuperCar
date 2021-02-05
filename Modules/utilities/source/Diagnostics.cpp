#include "Diagnostics.h"
#include <cmath>
#include <type_traits>
#include <cstdint>

Diagnostics::Diagnostics() : initial_time( std::chrono::steady_clock::now() )
{
	std::cout << "Diagnostics constructor called." << std::endl;
	openFileStream();

	// create the thread which process logged messages
	std::thread loggerThread = std::thread(
		[this]() {
			std::cout << "Diagnostics Log thread started." << std::endl;
			std::promise<bool> thread_terminate;
			log_thread_terminated = thread_terminate.get_future(); //in order to check thread termination

			processLogMessages();
			//this is executed after processLogMessages terminates (because the termination flag was set).
			thread_terminate.set_value(true);
			std::cout << "Diagnostics Log thread terminating." << std::endl;
		}
	);
	loggerThread.detach();


	// create the thread which process monitor messages
	std::thread monitorThread = std::thread(
		[this]() {
			std::cout << "Diagnostics Monitor thread started." << std::endl;
			std::promise<bool> thread_terminate;
			monitor_thread_terminated = thread_terminate.get_future(); //in order to check thread termination

			processMonitorMessage();
			//this is executed after processLogMessages terminates (because the termination flag was set).
			thread_terminate.set_value(true);
			std::cout << "Diagnostics Monitor thread terminating." << std::endl;
		}
	);
	monitorThread.detach();
}

Diagnostics::~Diagnostics()
{
	std::cout << "Diagnostics destructor called." << std::endl;
	
	//signal to the bakcground task to terminate and wait for them.
	terminate_flag = true;
	try {
		log_thread_terminated.wait();
		if (log_thread_terminated.get()) {
			std::cout << "Diagnostics Log thread termiated correctly." << std::endl;
		}
		monitor_thread_terminated.wait();
		if (monitor_thread_terminated.get()) {
			std::cout << "Diagnostics Monitor thread termiated correctly." << std::endl;
		}
	}
	catch (std::future_error e) {
		std::cout << "Diagnostics threads termination incorrect." << std::endl;

	}
	closeFileStream();
}

void Diagnostics::openFileStream() {
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

	if (fileStream.is_open()) {
		std::cout << "Logger file "+ logFile +" correctly initialized" << std::endl;
	}
	else {
		std::cout << "Logger file " + logFile + " initialization failed" << std::endl;
	}
}

void Diagnostics::closeFileStream() {
	// get current system clock time
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string string_time(30, '\0');
	std::strftime(&string_time[0], string_time.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - initial_time;
	writeToFile(LoggedElement(time, Topic::Simulation, Verbosity::Debug, "Logging file closed at: " + string_time));
	fileStream.close();
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



void Diagnostics::monitor(std::string key, std::string value) {
	std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - initial_time;
	MonitorElementValue newElement(time, value);
	{
		std::lock_guard<std::mutex> lk(monitorInputMutex);
		monitorInputQueue.push(MonitorElement(key, newElement));
	}
	monitorInputCond.notify_one();
}


void Diagnostics::processLogMessages() {
	while (true) {
		std::unique_lock<std::mutex> lk(logMutex);
		using namespace std::chrono_literals;
		logCond.wait_for(lk, 100ms,
			[this]() {
				return terminate_flag || !logQueue.empty();
			}
		);
		if (terminate_flag) {
			break;	// break the loop in case of termiation request
		}
		if (!logQueue.empty()) {
			LoggedElement newLog = logQueue.front();
			logQueue.pop();
			lk.unlock();
			addToLogQueue(newLog);
			writeToFile(newLog);
		}
	}
}

void Diagnostics::processMonitorMessage() {
	while (true) {
		std::unique_lock<std::mutex> lk(monitorInputMutex);
		using namespace std::chrono_literals;
		monitorInputCond.wait_for(lk, 100ms,
			[this]() {
				return terminate_flag || !monitorInputQueue.empty();
			}
		);
		if (terminate_flag) {
			break;	// break the loop in case of termiation request
		}
		if (!monitorInputQueue.empty()) {
			MonitorElement newLog = monitorInputQueue.front();
			monitorInputQueue.pop();
			lk.unlock();
			auto& [key, value] = newLog;
			addToMonitorMap(key, value);
		}
	}
}

void Diagnostics::addToMonitorMap(std::string key, MonitorElementValue value) {
	std::lock_guard<std::mutex> lk(monitorOutputMutex);
	monitorOutput.insert_or_assign(key, value);
}


void Diagnostics::addToLogQueue(LoggedElement element) {
	auto [time, topic, verbosity, message] = element;
	if (topic == Topic::Simulation) {
		std::lock_guard<std::mutex> lk(simulationLogMutex);
		simulationLogQueue.push(element);
	}
	else if (topic == Topic::Gui) {
		std::lock_guard<std::mutex> lk(guiLogMutex);
		guiLogQueue.push(element);
	}
	else if (topic == Topic::Viewer) {
		std::lock_guard<std::mutex> lk(viewerLogMutex);
		viewerLogQueue.push(element);
	}
}

std::string Diagnostics::getMonitorString() {
	std::string out;
	std::lock_guard<std::mutex> lk(monitorOutputMutex);
	for (const auto& element : monitorOutput) {
		auto [key, pair] = element;
		auto [time, value] = pair;
		out += key + "	" + value + "	" + logger_time_to_string(time) + "\n";
	}
	return out;
}

std::string Diagnostics::getLogString(Topic topic) {
	std::string tmp = "";
	if (topic == Topic::Simulation) {
		std::lock_guard<std::mutex> lk(simulationLogMutex);
		while (!simulationLogQueue.empty()) {
			auto [time, topic, verbosity, message] = simulationLogQueue.front();
			tmp += logger_time_to_string(time) + "	| " + verbosity_toString(verbosity) + "	| " + message + "\n";
			simulationLogQueue.pop();
		}
	}
	else if (topic == Topic::Gui) {
		std::lock_guard<std::mutex> lk(guiLogMutex);
		while (!guiLogQueue.empty()) {
			auto [time, topic, verbosity, message] = guiLogQueue.front();
			tmp += logger_time_to_string(time) + "	| " + verbosity_toString(verbosity) + "	| " + message + "\n";
			guiLogQueue.pop();
		}
	}
	else if (topic == Topic::Viewer) {
		std::lock_guard<std::mutex> lk(viewerLogMutex);
		while (!viewerLogQueue.empty()) {
			auto [time, topic, verbosity, message] = viewerLogQueue.front();
			tmp += logger_time_to_string(time) + "	| " + verbosity_toString(verbosity) + "	| " + message + "\n";
			viewerLogQueue.pop();
		}
	}
	return tmp;
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

std::string Diagnostics::logger_time_to_string(diagnostics_time time) {
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
