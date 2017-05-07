#pragma once
#include <vector>
#include "LogManager.h"

static class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);


private:
	IOManager* _instance;

};

