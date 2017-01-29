#pragma once
#include <string>

class CFloatLog
{
private:
	std::string file_name;
	bool verbose;

public:
	CFloatLog(std::string file_name, bool verbose = false);
	~CFloatLog();

	void add(unsigned int count, ...);
	void put_value(float value);
	void put_line();
	void put_separator(std::string separator = ",");
};

