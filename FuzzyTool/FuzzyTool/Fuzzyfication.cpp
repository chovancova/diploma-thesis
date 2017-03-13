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

	LogFile = fopen(file_name, "w");

	if (LogFile == nullptr)
	{
		MyError("Error LogFile in Fuzzyfication()\n");
	}
}

/**
 * \brief Descrutor fo fuzzyfication class. 
 */
Fuzzyfication::~Fuzzyfication()
{
	delete[] Intervals;

	fclose(LogFile);
}

void Fuzzyfication::RunFuzzification()
{
	InitializeDataset();


	unsigned long *new_result, count_result;
	unsigned int temp_interval;
	int does_entropy_decrease;
	float *result, *cluster, old_entropy, new_entropy;

	//initialize new name for file
	char filename_fuzzy[200];
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
	//DETERMINATION OF THE NUMBER OF INTERVALS
	//Set initial number of intervals I = 2; 
	CreateFeatures();

	fprintf(LogFile, "FilenameFuzzy=%s\n", filename_fuzzy);

	//For each dimension 
	for (unsigned int i = 0; i < InputAttr; i++)
	{
		printf("input attribute (dimension) = %d\n", i);
		if (LingvisticAttr[i] != 0)
		{
			Intervals[i] = LingvisticAttr[i];
			for (unsigned long x = 0; x < DatasetSize; x++)
			{
				temp_interval = (unsigned int)Features[x].Dimension[i];
				FuzzySetOnInterval[i][temp_interval][x] = 1.0f;
			}
		}
		else //real - value attribute (discretization of attributes) 
		{
			//to produce intrevals on each dimension 
			//to generate several triangular membership function for each real value attribute
			//a process also referred as the DISCRETIZATION OF ATTRIBUTES
			//some points need to be considered. 
			//First, the number of intervals on eaxh dimension needs to be dermined. 
			//Secound consideration, we emplooy the K-means clustering algorithm to find the interval centers, 
			//after the interval centers are detrmined, it is easy to decide on the WIDTH of each interval 
			does_entropy_decrease = 0;
			new_entropy = 1000000000.0;

			result = (float*)(newFloat(DatasetSize, 0.0, "Result )"));
			new_result = (unsigned long*)(newUnLong(DatasetSize, 0L, "NewResult "));
			count_result = CreateAscendingResult(i, result, new_result);

			do
			{
				old_entropy = new_entropy;
				if (does_entropy_decrease != 0)
				{
					ModifyFeatures(i, does_entropy_decrease);
				}
				//DETERMINATION OF THE NUMBER OF INTERVALS
				//Locate the centers of interval
				cluster = (float*)Center(i, result, new_result, count_result);
				//Assighn memberhsip function for each interval 
				AssignMembershipFunction(i, cluster);
				delete[] cluster;
				//Compute the total fuzzy entropy of all intervals for I and I-1 intervals. 
				new_entropy = EntropyCalculate(i);


				fprintf(LogFile, "i=%d  NoI[i]=%d  Hnew=%f\n\n", i, Intervals[i], new_entropy);

				if (does_entropy_decrease == -1 || Intervals[i] == count_result)
				{
					break;
				}

				if (new_entropy <= old_entropy)
				{
					does_entropy_decrease = 1;
				}
				else
				{
					break;
				}
			}
			while (true);
			WriteFuzzyficationLogs();
			std::cout << "Write Fuzzyfication Result to file.\n";
			WriteFuzzyficationResult(filename_fuzzy);

			delete[] result;
			delete[] new_result;
		}
	}
}


void Fuzzyfication::InitializeDataset() const
{
	ReadDataSets(IdDataset);
	Normalization();
}


/**
 * Membership function assigmnment is a procedure for assigning a membership function to each interval. 
 *
 */
void Fuzzyfication::AssignMembershipFunction(unsigned int attribute, float* center) const
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
			if ((Features[x].Dimension[attribute] >= center[interval]) // x >= c1
				&& (Features[x].Dimension[attribute] <= center[interval + 1])) //x <= c2
			{
				//the right-most interval , for x <= c2
				FuzzySetOnInterval[attribute][interval][x] =
					(center[interval + 1] - Features[x].Dimension[attribute]) //(c4 - x) / (c4 - c3)
					/
					(center[interval + 1] - center[interval]);

				//the left most interval x > c1 
				FuzzySetOnInterval[attribute][interval + 1][x] =
					(Features[x].Dimension[attribute] - center[interval]) // (x - c1) / (c2 - c1)
					/
					(center[interval + 1] - center[interval]);
			}
		}
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


void Fuzzyfication::CreateFeatures()
{
	unsigned int attr, intervals;

	for (attr = 0; attr < Attributes; attr++)
	{
		if (LingvisticAttr[attr] != 0)
		{
			Intervals[attr] = LingvisticAttr[attr];
		}
		else
		{
			//Set initial number of intervals to 2. 
			Intervals[attr] = 2;
		}
	}

	FuzzySetOnInterval = (float***) new float**[Attributes];
	if (!FuzzySetOnInterval)
		printf("Error allocation ***FuzzySetOnInterval in CreateFeatures(). ");

	for (attr = 0; attr < Attributes; attr++)
	{
		FuzzySetOnInterval[attr] = (float**) new float*[Intervals[attr]];
		if (!FuzzySetOnInterval[attr])
		{
			printf("Error allocation of memory for **Feature[attr] in CreateFeatures()");
		}

		for (intervals = 0; intervals < Intervals[attr]; intervals++)
		{
			FuzzySetOnInterval[attr][intervals] = (float*)newFloat(DatasetSize, 0.0, "FuzzySetOnInterval[attr][intervals] in CreateFeatures()");
		}
	}
	for (unsigned long x = 0; x < DatasetSize; x++) // Initialisation of Output Attribute
	{
		intervals = (unsigned int)Features[x].Dimension[InputAttr];
		FuzzySetOnInterval[InputAttr][intervals][x] = 1.0;
	}
}

void Fuzzyfication::ModifyFeatures(unsigned int attr, int interval_new_value) const
{
	for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
		delete[] FuzzySetOnInterval[attr][interval];
	delete[] FuzzySetOnInterval[attr];

	Intervals[attr] += interval_new_value;
	FuzzySetOnInterval[attr] = static_cast<float**>(new float*[Intervals[attr]]);
	if (!FuzzySetOnInterval[attr])
	{
		MyError("**FuzzySetOnInterval[attr] in ModifyFeatures()");
	}
	for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
	{
		FuzzySetOnInterval[attr][interval] = (float*)newFloat(DatasetSize, 0.0, "FuzzySetOnInterval[attr][interval] in ModifyFeatures()");
	}
}

void Fuzzyfication::DeleteFeatures() const
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


unsigned long Fuzzyfication::CreateAscendingResult(unsigned int i, float* Result, unsigned long* NewResult) const
{
	unsigned int new_item;
	unsigned long number_of_elements = 1;
	Result[0] = Features[0].Dimension[i];
	NewResult[0] = 1;
	for (unsigned long k = 1; k < DatasetSize; k++)
	{
		new_item = 1;
		for (unsigned long q = 0; q < number_of_elements; q++)
			if (Features[k].Dimension[i] == Result[q])
			{
				new_item = 0;
				NewResult[q]++;
			}
		if (new_item == 1)
		{
			Result[number_of_elements] = Features[k].Dimension[i];
			NewResult[number_of_elements] = 1;
			number_of_elements++;
		}
	}
	SortAscendingOrder(Result, NewResult, number_of_elements);
	return (number_of_elements);
}


void Fuzzyfication::SortAscendingOrder(float* result, unsigned long* new_result, unsigned long number_of_elements)
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


void Fuzzyfication::SortAscendingOrder(float* cut_points, unsigned int number_of_cutting_points)
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
