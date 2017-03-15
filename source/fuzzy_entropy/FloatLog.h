#pragma once
#include <string>

class Logger
{
private:
	FILE *f;
	std::string file_name;
	bool verbose;

public:
	Logger(std::string file_name, bool verbose = false);
	~Logger();

	void add(unsigned int count, ...);
	void put_value(float value);
	void put_line();
	void put_separator(std::string separator = ",");
};

