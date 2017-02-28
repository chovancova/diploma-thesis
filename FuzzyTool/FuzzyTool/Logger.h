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

	void add(unsigned int count, ...) const;
	void put_value(float value) const;
	void put_line() const;
	void put_separator(std::string separator = ",") const;
};

