#include "Fuzzyfication.h"
#include "TempFunctions.h"
#include <cstring>


/**
* \brief Initialize datasets, fuzzification,
* Set the initial number of Interval to 2.
* \param id_dataset Number of dataset.
*/
Fuzzyfication::Fuzzyfication(unsigned int id_dataset) : DataSets(id_dataset), Features(nullptr)
{
	IdDataset = id_dataset;

	///<code>Set the initial number of interval I = 2.</code> 
	Intervals = newUnInt(Attributes, 2, "Intervals in Fuzzy()");
	char NameLoggerFile[99];
	strcpy(NameLoggerFile, PATH_OUTPUT_FOLDER);
	strcat(NameLoggerFile, NameDataset);
	strcat(NameLoggerFile, ".log.txt");

	LoggerFile = fopen(NameLoggerFile, "w");

	if (LoggerFile == nullptr)
	{
		MyError("Error LoggerFile in Fuzzyfication()\n");
	}
}

/**
 * \brief Descrutor fo fuzzyfication class. 
 */
Fuzzyfication::~Fuzzyfication()
{
	delete[] Intervals;

	fclose(LoggerFile);
}

void Fuzzyfication::RunFuzzification()
{
	InitializeDataset();


	unsigned long *NewResult, countResult;
	unsigned int   temp_interval;
	int            doesEntropyDecrease, end; 
	float         *Result, *cluster, oldEntropy, newEntropy;

	//initialize new name for file
	char           FilenameFuzzy[200];
	strcpy(FilenameFuzzy, PATH_OUTPUT_FOLDER);
	strcat(FilenameFuzzy, NameDataset);
	strcat(FilenameFuzzy, ".cm.txt"); // cluster centers
	
	//DETERMINATION OF THE NUMBER OF INTERVALS
	//Set initial number of intervals I = 2; 
	CreateFeatures();

	fprintf(LoggerFile, "FilenameFuzzy=%s\n", FilenameFuzzy);

	//For each dimension 
	for (unsigned int i = 0; i<InputAttr; i++)   
	{
		printf("input attribute (dimension) = %d\n", i);
		if (LingvisticAttr[i] != 0)   
		{
			Intervals[i] = LingvisticAttr[i];
			for (unsigned long data_item = 0; data_item<DatasetSize; data_item++)
			{
				temp_interval = (unsigned int)Items[data_item].Dimension[i];
				Features[i][temp_interval][data_item] = 1.0f;
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
			doesEntropyDecrease = 0;
			end = 0;
			newEntropy = 1000000000.0;

			Result = static_cast<float*>(newFloat(DatasetSize, 0.0, "Result )"));
			NewResult = static_cast<unsigned long*>(newUnLong(DatasetSize, 0L, "NewResult "));
			countResult = CreateAscendingResult(i, Result, NewResult);
	
			do {
				oldEntropy = newEntropy;
				if (doesEntropyDecrease != 0)
				{
					ModifyFeatures(i, doesEntropyDecrease);
				}
				//DETERMINATION OF THE NUMBER OF INTERVALS
				//Locate the centers of interval
				cluster = (float*)Center(i, Result, NewResult, countResult); 
				//Assighn memberhsip function for each interval 
				AssignMembershipFunction(i, cluster);
				delete[] cluster;
				//Compute the total fuzzy entropy of all intervals for I and I-1 intervals. 
				newEntropy = EntropyCalculate(i);
				

				fprintf(LoggerFile, "i=%d  NoI[i]=%d  Hnew=%f\n\n", i, Intervals[i], newEntropy);
			
				if(end == 1 || doesEntropyDecrease == -1 || Intervals[i]==countResult)
				{
					break;
				}

				if(newEntropy <= oldEntropy)
				{
					doesEntropyDecrease = 1;
				}else
				{
					doesEntropyDecrease = 1;
					end = 1;
				}
																									
			} while (1);
			WriteFuzzyficationLogs();
			delete[] Result;
			delete[] NewResult;
		}
	} 
}


void Fuzzyfication::InitializeDataset() const
{
	ReadDataSets(IdDataset);
	Normalization();
	
}


void Fuzzyfication::AssignMembershipFunction(unsigned attribute, float* c) const
{
	for (unsigned long data_item = 0; data_item<DatasetSize; data_item++)
	{
		for (unsigned int interval = 0; interval < Intervals[attribute]; interval++)
		{
			Features[attribute][interval][data_item] = 0;
		}

		for (unsigned int interval = 0; interval<Intervals[attribute] - 1; interval++){
			if ((Items[data_item].Dimension[attribute] >= c[interval])  // x >= c1
				&& (Items[data_item].Dimension[attribute] <= c[interval + 1])) //x <= c2
			{
				//the right-most interval , for x <= c2
				Features[attribute][interval][data_item] =
					(c[interval + 1] - Items[data_item].Dimension[attribute]) //(c4 - x) / (c4 - c3)
					/ 
					(c[interval + 1] - c[interval]);

				//the left most interval x > c1 
				Features[attribute][interval + 1][data_item] = 
					(Items[data_item].Dimension[attribute] - c[interval])   // (x - c1) / (c2 - c1)
					/ 
					(c[interval + 1] - c[interval]);
			}
		}
		if (Items[data_item].Dimension[attribute] < c[0]) //x < c1
		{
			Features[attribute][0][data_item] = 1.0;
		}
		if (Items[data_item].Dimension[attribute] > c[Intervals[attribute] - 1])  //x > c1 - 1
		{
			Features[attribute][Intervals[attribute] - 1][data_item] = 1.0;  
		}
	}  

}




void Fuzzyfication::CreateFeatures()
{
	unsigned int attr, intervals;

	for (attr = 0; attr < Attributes; attr++) {
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

	Features = static_cast<float***>(new float**[Attributes]);
	if (!Features)
		printf("Error allocation ***Features in CreateFeatures(). ");

	for (attr = 0; attr< Attributes; attr++)
	{
		Features[attr] = (float**) new float*[Intervals[attr]];
		if (!Features[attr]) {
			printf("Error allocation of memory for **Feature[attr] in CreateFeatures()");
		}

		for (intervals = 0; intervals < Intervals[attr]; intervals++)
		{
			Features[attr][intervals] = (float*)newFloat(DatasetSize, 0.0, "Features[attr][intervals] in CreateFeatures()");
		}
	}

}

void Fuzzyfication::ModifyFeatures(unsigned int attr, int interval_new_value) const
{
	for (unsigned int interval = 0; interval<Intervals[attr]; interval++)
		delete[] Features[attr][interval];
	delete[] Features[attr];

	Intervals[attr] += interval_new_value;
	Features[attr] = static_cast<float**>(new float*[Intervals[attr]]);
	if (!Features[attr])
	{
		MyError("**Features[attr] in ModifyFeatures()");
	}
	for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
	{
		Features[attr][interval] = (float*)newFloat(DatasetSize, 0.0, "Features[attr][interval] in ModifyFeatures()");
	}
}

void Fuzzyfication::DeleteFeatures() const
{
	for (unsigned int i = 0; i<Attributes; i++)
	{
		for (unsigned int j = 0; j < Intervals[i]; j++)
		{
			delete[] Features[i][j];
		}
		delete[] Features[i];
	}
	delete[] Features;
}


unsigned long Fuzzyfication::CreateAscendingResult(unsigned int i, float *Result, unsigned long *NewResult) const
{
	unsigned int  newItem;
	unsigned long numberOfElements = 1;
	Result[0] = Items[0].Dimension[i];
	NewResult[0] = 1;
	for (unsigned long k = 1; k<DatasetSize; k++)
	{
		newItem = 1;
		for (unsigned long q = 0; q<numberOfElements; q++)
			if (Items[k].Dimension[i] == Result[q])
			{
				newItem = 0; NewResult[q]++;
			}
		if (newItem == 1)
		{
			Result[numberOfElements] = Items[k].Dimension[i]; NewResult[numberOfElements] = 1; numberOfElements++;
		}
	}
	SortAscendingOrder(Result, NewResult, numberOfElements);
	return(numberOfElements);
}



void Fuzzyfication::SortAscendingOrder(float *Result, unsigned long *NewResult, unsigned long numberOfElements)
{
	unsigned long i;
	unsigned long index = 0L;
	unsigned long value;
	float         min;

	do {
		min = Result[index];
		i = index;

		for (unsigned long k = index + 1; k<numberOfElements; k++) {
			if (Result[k] < min)
			{
				min = Result[k];
				i = k;
			}
		}

		Result[i] = Result[index];
		Result[index] = min;

		value = NewResult[i];

		NewResult[i] = NewResult[index];
		NewResult[index] = value;

		index++;
	} while (index < numberOfElements - 1);
}


void Fuzzyfication::SortAscendingOrder(float *PointsOfCut, unsigned int numberOfCutPoints)
{
	unsigned int i, num, index = 0;
	float min;
	do {
		min = PointsOfCut[index];
		num = index;
		for (i = index + 1; i<numberOfCutPoints; i++)
			if (PointsOfCut[i] < min) { min = PointsOfCut[i]; num = i; }
		PointsOfCut[num] = PointsOfCut[index];
		PointsOfCut[index] = min;
		index++;
	} while (index < numberOfCutPoints - 1);
}
