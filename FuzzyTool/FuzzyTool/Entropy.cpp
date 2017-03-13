#include "Fuzzyfication.h"
#include "TempFunctions.h"
#include <cmath>

float Fuzzyfication::EntropyCalculate(unsigned int attr)
{
	//1) Let X = {r1, ... , rn} be a universal set with elements ri distributed in pattern space where i = 1..n. 
	//2) Let A be a fuzzy set defined on a interval of pattern space which kontains k elements (k < n). 


	//classes 
	unsigned int j = 0;
	unsigned int ja = 0;
	unsigned int jb = 0;
	unsigned int class_m = 0;
	unsigned long* countM;
	float ***MU, **sum_mu;
	float new_entropy = 0.0f;
	float total_fuzzy_entropy = 0.0f;
	float max = 0.0f;
	float p = 0.0f;
	countM = static_cast<unsigned long*>(newUnLong(Intervals[attr], 0L, "countM in EntropyCalc()"));

	MU = (float***) new float**[Intervals[attr]];
	sum_mu = (float**) new float*[Intervals[attr]];

	if (!MU || !sum_mu) MyError("Error allocation of (M and sumM) in EntropyCalculate()");
	for (class_m = 0; class_m < Intervals[attr]; class_m++)
	{
		sum_mu[class_m] = (float*)(newFloat(Intervals[attr], 0, "sumM(EntropyCalc)"));
		MU[class_m] = (float**)(new float*[Intervals[attr]]);

		if (!MU[class_m])
		{
			MyError("Error allocation of (M[sector]) in EntropyCalcululate()");
		}

		for (ja = 0; ja < Intervals[attr]; ja++)
		{
			MU[class_m][ja] = static_cast<float*>(newFloat(OutputIntervals, 0, "M in EntropyCalc()"));
		}
	}

	for (unsigned long data_item = 0; data_item < DatasetSize; data_item++)
	{
		max = FuzzySetOnInterval[attr][0][data_item];
		//SCJ - set of elements of class j on the universal set X. 
		//It is a subset of the universal X. 
		for (j = 0; j < Intervals[attr]; j++)
		{
			if (max <= FuzzySetOnInterval[attr][j][data_item])
			{
				class_m = j;
				max = FuzzySetOnInterval[attr][j][data_item];
			}
		}
		countM[class_m]++;

		// Membership Degree Calculation
		for (ja = 0; ja < Intervals[attr]; ja++)
		{
			for (jb = 0; jb < OutputIntervals; jb++)
			{
				MU[class_m][ja][jb] += FuzzySetOnInterval[attr][ja][data_item] * FuzzySetOnInterval[InputAttr][jb][data_item];
			}
		}
	}

	// Wage Degree Calculation
	for (class_m = 0; class_m < Intervals[attr]; class_m++)
		for (ja = 0; ja < Intervals[attr]; ja++)
			for (jb = 0; jb < OutputIntervals; jb++)
				sum_mu[class_m][ja] += MU[class_m][ja][jb];

	for (class_m = 0; class_m < Intervals[attr]; class_m++)
		fprintf(LogFile, "countM[%d]=%d\n", class_m, countM[class_m]);

	//  Fuzzy Entropy Calculation
	// The fuzzy entropy FE on the universal uset X for the elements within an interval 
	total_fuzzy_entropy = 0.0;
	for (class_m = 0; class_m < Intervals[attr]; class_m++)
	{
		new_entropy = 0.0;
		for (ja = 0; ja < Intervals[attr]; ja++)
			for (jb = 0; jb < OutputIntervals; jb++)
			{
				p = static_cast<float>(sum_mu[class_m][ja] == 0) ? 0 : (MU[class_m][ja][jb] / sum_mu[class_m][ja]);
				new_entropy -= (MU[class_m][ja][jb] == 0) ? 0 : p * log2(p);
				//	fprintf(LogFile, "dimension=%d, jb=%d, p=%f New Entropy =%f\n", class_m, jb, p, new_entropy);
			}

		total_fuzzy_entropy += new_entropy * (float)countM[class_m] / DatasetSize;
	}

	// delete M and sumM
	for (class_m = 0; class_m < Intervals[attr]; class_m++)
	{
		for (ja = 0; ja < Intervals[attr]; ja++)
			delete[] MU[class_m][ja];
		delete[] MU[class_m];
		delete[] sum_mu[class_m];
	}
	delete[] MU;
	delete[] sum_mu;
	delete[] countM;
	return total_fuzzy_entropy;
}
