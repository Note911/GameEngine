#include "LogManager.h"

LogManager *LogManager::_instance = nullptr;

LogManager::LogManager() {
	_outStream = NULL;
	fileName = "logfile.log";
	_currentLogLevel = LOG_ERROR;
}


LogManager::~LogManager() {
	close();
}


LogManager& LogManager::getInstance(void) {
	if (_instance == NULL) {
		_instance = new LogManager();
	}
	return *_instance;
}

void LogManager::setLogFile(std::string &fileName) {
	close();
	_outStream = new std::ofstream(fileName.c_str());
	_currentLogLevel = LOG_ERROR;
}

void LogManager::close() {
	if (_outStream != NULL) {
		_outStream->close();
		delete _outStream;
		_outStream = NULL;
	}
}

void LogManager::log(LogLevel severity, std::string msg) {
	//check if the log level should allow the messege to show
	if (severity <= _currentLogLevel && _currentLogLevel > LOG_NONE) {
		if (_outStream == NULL)
			setLogFile(fileName);
		(*_outStream) << msg << "\n";
		_outStream->flush();
	}
}