#include <stdio.h>
#include <stdarg.h>
#include <string>
#include "Logger.h"


Logger::Logger(std::string file_name, bool verbose)
{
	this->file_name = file_name;
	this->verbose = verbose;

	f = fopen(file_name.c_str(), "w");
	if (f < 0)
	{
		perror("Fail to open log file. ");
	}
}


Logger::~Logger()
{
	fclose(f);
}


void Logger::add(unsigned int count, ...) 
{
	if (f < 0)
	{
		return;
	}

	va_list valist;

	va_start(valist, count);

	for (unsigned int i = 0; i < count; i++)
	{
		float tmp = va_arg(valist, double);
		fprintf(f, "%6.3f\t ", tmp);

		if (verbose)
			printf("%6.3f\t ", tmp);
	}

	fprintf(f, "\n");

	if (verbose)
		printf("\n");


	va_end(valist);

	fflush(f);
}

void Logger::put_value(float value) 
{
	if (f < 0)
	{
		return;
	}
	fprintf(f, "%6.3f\t ", value);

	if (verbose)
		printf("%6.3f\t ", value);
	fflush(f);
}

void Logger::put_line() 
{
	if (f < 0)
	{
		return;
	}
	fprintf(f, "\n");

	if (verbose)
		printf("\n");
	fflush(f);
}

void Logger::put_separator(std::string separator) 
{
	if (f < 0)
	{
		return;
	}
	fprintf(f, "%s", separator.c_str());

	if (verbose)
		printf("%s", separator.c_str());

	fflush(f);
}
