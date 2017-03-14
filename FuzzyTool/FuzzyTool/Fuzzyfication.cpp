#include "Fuzzyfication.h"
#include "TempFunctions.h"
#include <cstring>
#include <iostream>
#include <ctime>


/**
* \brief Initialize datasets, fuzzification,
* Set the initial number of Interval to 2.
* \param id_dataset Number of dataset.
*/
Fuzzyfication::Fuzzyfication(unsigned int id_dataset) : DataSets(id_dataset), FuzzySetOnInterval(nullptr)
{
	IdDataset = id_dataset;

	///<code>Set the initial number of interval I = 2.</code> 
	Intervals = newUnInt(Attributes, 2, "Intervals in Fuzzy()");
	char file_name[99];
	strcpy(file_name, PATH_OUTPUT_FOLDER);
	strcat(file_name, NameDataset);
	strcat(file_name, ".log.txt");

	LogFile = fopen(file_name, "a+");

	if (LogFile == nullptr)
	{
		MyError("Error LogFile in Fuzzyfication()\n");
	}
}

/**
 * \brief Desctructor fo fuzzyfication class. 
 */
Fuzzyfication::~Fuzzyfication()
{
	delete[] Intervals;

	fclose(LogFile);
}

void Fuzzyfication::RunFuzzification(unsigned int method)
{
	switch (method)
	{
	case 1: run_fuzzification_febfc();
		break;
	default: run_fuzzification_febfc();
		break;
	}
}

void Fuzzyfication::run_fuzzification_febfc()
{
	char filename_fuzzy[200];
	initialize_filename(filename_fuzzy);
	
	fprintf(LogFile, "**********************************************************************************\n");
	fprintf(LogFile, "File name of fuzzy results:\t %s\n", filename_fuzzy);

	initialize_dataset();

	unsigned long *new_result, count_result;
	int does_entropy_decrease;
	float *result, *cluster, old_entropy, new_entropy;

	/////////////////////////////////////////////STEP 1////////////////////////////////////////////////

	//DETERMINATION OF THE NUMBER OF INTERVALS
	//Set initial number of intervals I = 2; 
	febfc_step_1_create_features();

	//For each dimension 
	for (unsigned int dimension = 0; dimension < InputAttributes; dimension++)
	{
		print_to_console_dimension(dimension);

		if (LingvisticAttributes[dimension] != 0)
		{
			set_lingvistic_attributes(dimension);
		}
		else //real - value attribute (discretization of attributes) 
		{
			initialize_variables_for_entropy_result(new_result, count_result, does_entropy_decrease, result, new_entropy, dimension);
		do
			{
				old_entropy = new_entropy;
				if (does_entropy_decrease != 0)
				{
					modify_features(dimension, does_entropy_decrease);
				}
				/////////////////////////////////////////////STEP 2////////////////////////////////////////////////
				//DETERMINATION OF THE NUMBER OF INTERVALS
				//Locate the centers of interval
				cluster = (float*)febfc_step_2_locate_center_of_interval(dimension, result, new_result, count_result);

				/////////////////////////////////////////////STEP 3////////////////////////////////////////////////
				//Assighn memberhsip function for each interval 
				febfc_step_3_assign_membership_function(dimension, cluster);

				delete[] cluster;
				/////////////////////////////////////////////STEP 4////////////////////////////////////////////////
				//Compute the total fuzzy entropy of all intervals for I and I-1 intervals. 
				new_entropy = febfc_step_4_compute_total_fuzzy_entropy(dimension);

				print_to_log_file_new_entropy(new_entropy, dimension);

				/////////////////////////////////////////////STEP 5////////////////////////////////////////////////
				if (febfc_step_5_does_entropy_decrese(count_result, does_entropy_decrease, old_entropy, new_entropy, dimension)) break;
			} while (true);
		
			WriteFuzzyficationLogs();
			
			std::cout << "Write Fuzzyfication Result to file.\n";
			
			print_to_cm_file_results(filename_fuzzy);

			delete[] result;
			delete[] new_result;
		}
	}
}






void Fuzzyfication::set_lingvistic_attributes(unsigned int dimension) const
{
	unsigned int temp_interval;
	Intervals[dimension] = LingvisticAttributes[dimension];
	for (unsigned long x = 0; x < DatasetSize; x++)
	{
		temp_interval = (unsigned int)Features[x].Dimension[dimension];
		FuzzySetOnInterval[dimension][temp_interval][x] = 1.0f;
	}
}

void Fuzzyfication::initialize_variables_for_entropy_result(unsigned long*& new_result, unsigned long& count_result, int& does_entropy_decrease, float*& result, float& new_entropy, unsigned dimension) const
{
	does_entropy_decrease = 0;
	new_entropy = 1000000000.0;
	result = (float*)(newFloat(DatasetSize, 0.0, "Result )"));
	new_result = (unsigned long*)(newUnLong(DatasetSize, 0L, "NewResult "));

	count_result = create_ascending_result(dimension, result, new_result);
}

bool Fuzzyfication::febfc_step_5_does_entropy_decrese(unsigned long count_result, int& does_entropy_decrease, float old_entropy, float new_entropy, unsigned dimension) const
{
	if (does_entropy_decrease == -1 || Intervals[dimension] == count_result)
	{
		return true;
	}

	if (new_entropy <= old_entropy)
	{
		does_entropy_decrease = 1;
	}
	else
	{
		return true;
	}
	return false;
}

void Fuzzyfication::print_to_log_file_new_entropy(float new_entropy, unsigned dimension) const
{
	fprintf(LogFile, "\nDimension:\t %d  \nNumber of interval in dimension:\t %d  \nNew Entropy:\t %f\n\n", dimension, Intervals[dimension], new_entropy);
}

void Fuzzyfication::print_to_console_dimension(unsigned dimension)
{
	printf("\nInput attributes (dimension):\t %d\n", dimension);
}


void Fuzzyfication::initialize_dataset() const
{
	ReadDataSets(IdDataset);
	Normalization();
}


/***
 * Membership function assigmnment is a procedure for assigning a membership function to each interval. 
 */
 //-------------------------------III.C--MEMBERSHIP FUNCTION ASSIGMENT---------------------------------------
 //-------------------------------CASE 1 - THE LEFT-MOST INTERVAL -------------------------------------------
 //-------------------------------CASE 2 - THE RIGHT-MOST INTERVAL -------------------------------------------
 //-------------------------------CASE 3 - THE INTERNAL INTERVAL -------------------------------------------
void Fuzzyfication::febfc_step_3_assign_membership_function(unsigned int attribute, float* center) const
{
	//All X = x1..xn
	for (unsigned long x = 0; x < DatasetSize; x++)
	{
		for (unsigned int interval = 0; interval < Intervals[attribute]; interval++)
		{
			FuzzySetOnInterval[attribute][interval][x] = 0;
		}

		for (unsigned int interval = 0; interval < Intervals[attribute] - 1; interval++)
		{
			if ((Features[x].Dimension[attribute] >= center[interval])			// x >= c1
				&& (Features[x].Dimension[attribute] <= center[interval + 1]))  //x <= c2
			{
				//-------------------------------CASE 2 - THE RIGHT-MOST INTERVAL -------------------------------------------
				//the right-most interval , for x <= c2
				FuzzySetOnInterval[attribute][interval][x] =
					(center[interval + 1] - Features[x].Dimension[attribute]) //(c4 - x) / (c4 - c3)
					/
					(center[interval + 1] - center[interval]);

				//-------------------------------CASE 1 - THE LEFT-MOST INTERVAL -------------------------------------------
				//the left most interval x > c1 
				FuzzySetOnInterval[attribute][interval + 1][x] =
					(Features[x].Dimension[attribute] - center[interval]) // (x - c1) / (c2 - c1)
					/
					(center[interval + 1] - center[interval]);
			}
		}

		//-------------------------------CASE 3 - THE INTERNAL INTERVAL -------------------------------------------
		if (Features[x].Dimension[attribute] < center[0]) //x < c1
		{
			FuzzySetOnInterval[attribute][0][x] = 1.0;
		}

		if (Features[x].Dimension[attribute] > center[Intervals[attribute] - 1]) //x > c1 - 1
		{
			FuzzySetOnInterval[attribute][Intervals[attribute] - 1][x] = 1.0;
		}
	}
}


void Fuzzyfication::febfc_step_1_create_features()
{
	unsigned int attr, intervals;

	for (attr = 0; attr < Attributes; attr++)
	{
		if (LingvisticAttributes[attr] != 0)
		{
			Intervals[attr] = LingvisticAttributes[attr];
		}
		else
		{
			//Set initial number of intervals to 2. 
			Intervals[attr] = 2;
		}
	}

	FuzzySetOnInterval = (float***) new float**[Attributes];
	if (!FuzzySetOnInterval)
		printf("Error allocation ***FuzzySetOnInterval in febfc_step_1_create_features(). ");

	for (attr = 0; attr < Attributes; attr++)
	{
		FuzzySetOnInterval[attr] = (float**) new float*[Intervals[attr]];
		if (!FuzzySetOnInterval[attr])
		{
			printf("Error allocation of memory for **Feature[attr] in febfc_step_1_create_features()");
		}

		for (intervals = 0; intervals < Intervals[attr]; intervals++)
		{
			FuzzySetOnInterval[attr][intervals] = (float*)newFloat(DatasetSize, 0.0, "FuzzySetOnInterval[attr][intervals] in febfc_step_1_create_features()");
		}
	}
	for (unsigned long x = 0; x < DatasetSize; x++) // Initialisation of Output Attribute
	{
		intervals = (unsigned int)Features[x].Dimension[InputAttributes];
		FuzzySetOnInterval[InputAttributes][intervals][x] = 1.0;
	}
}

void Fuzzyfication::modify_features(unsigned int attr, int interval_new_value) const
{
	for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
		delete[] FuzzySetOnInterval[attr][interval];
	delete[] FuzzySetOnInterval[attr];

	Intervals[attr] += interval_new_value;
	FuzzySetOnInterval[attr] = static_cast<float**>(new float*[Intervals[attr]]);
	if (!FuzzySetOnInterval[attr])
	{
		MyError("**FuzzySetOnInterval[attr] in modify_features()");
	}
	for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
	{
		FuzzySetOnInterval[attr][interval] = (float*)newFloat(DatasetSize, 0.0, "FuzzySetOnInterval[attr][interval] in modify_features()");
	}
}

void Fuzzyfication::delete_features() const
{
	for (unsigned int i = 0; i < Attributes; i++)
	{
		for (unsigned int j = 0; j < Intervals[i]; j++)
		{
			delete[] FuzzySetOnInterval[i][j];
		}
		delete[] FuzzySetOnInterval[i];
	}
	delete[] FuzzySetOnInterval;
}


unsigned long Fuzzyfication::create_ascending_result(unsigned int dimension, float* Result, unsigned long* NewResult) const
{
	unsigned int new_item;
	unsigned long number_of_elements = 1;
	Result[0] = Features[0].Dimension[dimension];
	NewResult[0] = 1;
	for (unsigned long k = 1; k < DatasetSize; k++)
	{
		new_item = 1;
		for (unsigned long q = 0; q < number_of_elements; q++)
			if (Features[k].Dimension[dimension] == Result[q])
			{
				new_item = 0;
				NewResult[q]++;
			}
		if (new_item == 1)
		{
			Result[number_of_elements] = Features[k].Dimension[dimension];
			NewResult[number_of_elements] = 1;
			number_of_elements++;
		}
	}
	sort_ascending_order(Result, NewResult, number_of_elements);
	return (number_of_elements);
}


void Fuzzyfication::sort_ascending_order(float* result, unsigned long* new_result, unsigned long number_of_elements)
{
	unsigned long i;
	unsigned long index = 0L;
	unsigned long value;
	float min;

	do
	{
		min = result[index];
		i = index;

		for (unsigned long k = index + 1; k < number_of_elements; k++)
		{
			if (result[k] < min)
			{
				min = result[k];
				i = k;
			}
		}

		result[i] = result[index];
		result[index] = min;

		value = new_result[i];

		new_result[i] = new_result[index];
		new_result[index] = value;

		index++;
	}
	while (index < number_of_elements - 1);
}


void Fuzzyfication::sort_ascending_order(float* cut_points, unsigned int number_of_cutting_points)
{
	unsigned int i, num, index = 0;
	float min;
	do
	{
		min = cut_points[index];
		num = index;
		for (i = index + 1; i < number_of_cutting_points; i++)
			if (cut_points[i] < min)
			{
				min = cut_points[i];
				num = i;
			}
		cut_points[num] = cut_points[index];
		cut_points[index] = min;
		index++;
	}
	while (index < number_of_cutting_points - 1);
}


void Fuzzyfication::initialize_filename(char (&filename_fuzzy)[200])
{
	strcpy(filename_fuzzy, PATH_OUTPUT_FOLDER);

	time_t raw_time;
	std::tm* time_info;
	char buffer[20];
	time(&raw_time);
	time_info = std::localtime(&raw_time);
	std::strftime(buffer, 20, "%Y-%m-%d-%H-%M-%S", time_info);
	std::puts(buffer);
	strcat(filename_fuzzy, NameDataset);
	strcat(filename_fuzzy, "_");
	strcat(filename_fuzzy, buffer);
	strcat(filename_fuzzy, ".cm.txt"); // cluster centers
}
