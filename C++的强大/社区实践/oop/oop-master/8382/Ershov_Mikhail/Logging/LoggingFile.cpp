#include "LoggingFile.h"

LoggingFile::LoggingFile(string file) { 
	outFile.open(file); 
}

LoggingFile::~LoggingFile() { 
	outFile.close();
}

void LoggingFile::log(const string& str) { 
	outFile << str;
}