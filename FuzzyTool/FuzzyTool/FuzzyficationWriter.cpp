#include "Fuzzyfication.h"
#include "TempFunctions.h"

void Fuzzyfication::print_to_file_number_of_interval_for_each_attributes(FILE* file) const
{
	for (unsigned int attr = 0; attr < Attributes; attr++)
	{
		fprintf(file, "%4d ", Intervals[attr]);
	}
}

void Fuzzyfication::print_to_file_fuzzification_result_all_attributes(FILE* file) const
{
	for (unsigned long dataset_value = 0; dataset_value < DatasetSize; dataset_value++)
	{
		for (unsigned int attr = 0; attr < Attributes; attr++)
		{
			for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
			{
				fprintf(file, "%f ", FuzzySetOnInterval[attr][interval][dataset_value]);
			}
			fprintf(file, "\t");
		}
		fprintf(file, "\n");
	}
}

int Fuzzyfication::print_to_cm_file_results(char* filename) const
{
	FILE* file;
	file = fopen(filename, "w");
	if (file == nullptr)
	{
		MyError("Error FileNameOut in Fuzzy::WriteFuzzyFile()\n");
		return -1;
	}

	//print dataset size, number of input attributes,  number of output attributes
	fprintf(file, "%ld\n%d %d\n", DatasetSize, InputAttributes, OutputAttributes);

	//print number of interval for each attributes. 
	print_to_file_number_of_interval_for_each_attributes(file);
	fprintf(file, "\n\n");

	//Write fuzzification values for all attributes 
	print_to_file_fuzzification_result_all_attributes(file);
	fclose(file);
	return 1;
}

int Fuzzyfication::print_to_log_file_temporary_results() const
{
	fprintf(LogFile, "\n ----------------------------------- TEMPORARY RESULTS ------------------------------------------: \n");

	fprintf(LogFile, "Dataset size:\t\t\t%ld\nNumber of Input Attributes:\t\t\t%d\nOutput Attr:\t\t\t%d\n", DatasetSize, InputAttributes, OutputAttributes);

	//print number of interval for each attributes. 
	fprintf(LogFile, "Intervals: \n");
	print_to_file_number_of_interval_for_each_attributes(LogFile);

	fprintf(LogFile, "\n");
	//Write fuzzification values for all attributes 
	print_to_file_fuzzification_result_all_attributes(LogFile);

	fprintf(LogFile, "\n -----------------------------------------------------------------------------------------------: \n");

	return 1;
}
