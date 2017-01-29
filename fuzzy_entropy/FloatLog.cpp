#include "FloatLog.h"
#include <stdio.h>
#include <stdarg.h>
#include <cstdarg>
#include <cstdarg>


CFloatLog::CFloatLog(std::string file_name, bool verbose)
{
	this->file_name = file_name;
	this->verbose = verbose;

	FILE *f = fopen(file_name.c_str(), "w");
	fclose(f);
}


CFloatLog::~CFloatLog()
{

}


void CFloatLog::add(unsigned int count, ...)
{
	FILE *f = fopen(file_name.c_str(), "a+");

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

	fclose(f);
}

void CFloatLog::put_value(float value)
{
	FILE *f = fopen(file_name.c_str(), "a+");

	fprintf(f, "%6.3f\t ", value);

	if (verbose)
		printf("%6.3f\t ", value);
	fclose(f);
}

void CFloatLog::put_line()
{
	FILE *f = fopen(file_name.c_str(), "a+");

	fprintf(f, "\n");

	if (verbose)
		printf("\n");
	fclose(f);
}

void CFloatLog::put_separator(std::string separator)
{
	FILE *f = fopen(file_name.c_str(), "a+");

	fprintf(f, "%s", separator.c_str());

	if (verbose)
		printf("%s", separator.c_str());

	fclose(f);
}