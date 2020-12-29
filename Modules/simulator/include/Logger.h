#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger
{
private:
	std::string fileName = "D:\\WorkSpace\\supercar\\logs\\logs.txt";
	std::ofstream logFileStream;
public:
	Logger();
	~Logger();
	void initialize();
	void log(std::string logMessage);
};

#endif