#pragma once
#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <fstream>
#include <iomanip>
#include <string>

class LogManager {
	public:
		enum LogLevel { LOG_NONE, LOG_ERROR, LOG_WARNING, LOG_TRACE, LOG_INFO };
		std::string fileName;

	private:
		std::ofstream *_outStream;
		static LogManager *_instance;
		LogLevel _currentLogLevel;
		//private constructor because singleton
		LogManager(void);

	public:
		//destructor
		~LogManager(void);
		//returns the instanace of the log manager
		static LogManager& getInstance();
		//Sets the log file
		void setLogFile(std::string &fileName);
		//closes the log file
		void close();
		//sets the severity of the log level
		void setSeverity(LogLevel severity) {
			_currentLogLevel = severity;
		}
		//Returns the current severity of the log 
		LogLevel getLogLevel() {
			return _currentLogLevel;
		}
		//Logs a message to the file at the current severity
		void log(LogLevel severity, std::string msg);
		//Logs an error
		void error(std::string msg) {
			log(LOG_ERROR, msg);
		}
		//Log a warning
		void warning(std::string msg) {
			log(LOG_WARNING, msg);
		}
		//Log a trace
		void trace(std::string msg){
			log(LOG_TRACE, msg); }
		//Log info
		void info(std::string msg) {
			log(LOG_INFO, msg);
		}

};
#endif
