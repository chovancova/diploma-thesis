#include "Fuzzyfication.h"
#include "TempFunctions.h"

int Fuzzyfication::WriteFuzzyficationResult(char* filename) const
{
	FILE *file;
	file = fopen(filename, "w");
	if (file == nullptr)
	{
		MyError("Error FileNameOut in Fuzzy::WriteFuzzyFile()\n");
		return -1;
	}


	fprintf(file, "%ld\n%d %d\n", DatasetSize, InputAttr, OutputAttr);

	for (unsigned int attr = 0; attr< Attributes; attr++)
	{
		fprintf(file, "%4d ", Intervals[attr]);
	}
	fprintf(file, "\n");


	for (unsigned int attr = 0; attr < InputAttr; attr++)
	{
		fprintf(file, "%4.2f ", 1.0);
	}
	
	fprintf(file, "\n");
	
	//Write all attributes 
	for (unsigned long dataset_value = 0; dataset_value<DatasetSize; dataset_value++)
	{
		for (unsigned int attr = 0; attr<Attributes; attr++)
		{
			for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
			{
				fprintf(file, "%f ", Features[attr][interval][dataset_value]);
			}
			fprintf(file, "\t");
		}
		fprintf(file, "\n");
	}
	fclose(file);
	return 1;
}

int Fuzzyfication::WriteFuzzyficationLogs() const
{
	fprintf(LoggerFile, "\n\nDataset size: %ld\nNumber of Input Attributes: %d \t Output Attr:  %d\n", DatasetSize,InputAttr, OutputAttr);
	
	fprintf(LoggerFile, "\n Intervals: ");
	
	for (unsigned int i = 0; i < Attributes; i++)
	{
		fprintf(LoggerFile, "%4d ", Intervals[i]);
	}   
	
	fprintf(LoggerFile, "\n Input Attributters: ");

	for (unsigned int i = 0; i<InputAttr; i++)
	{		
		fprintf(LoggerFile, "%4.2f ", 1.0);      
	}

	fprintf(LoggerFile, "\n Temp Results : ");
	
	for (unsigned long k = 0; k<DatasetSize; k++)
	{
		for (unsigned int i = 0; i<Attributes; i++)
		{
			for (unsigned int j = 0; j<Intervals[i]; j++)
				fprintf(LoggerFile, "%7.4f ", Features[i][j][k]);
			fprintf(LoggerFile, " \t ");
		}
		fprintf(LoggerFile, "\n");
	}
	return 1;
}

