#include "Fuzzyfication.h"
#include "TempFunctions.h"
#include <cmath>


//---------------------------II.C.--FUZZY ENTROPY OF AN INTERVAL FOR EACH FEATURE DIMENSION---------------------------------------
//---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
//---------------------------II.C.----STEP 2 - SET FUZZY SET A CONTAINS K ELEMENTS ---------------------------
//---------------------------II.C.----STEP 3 - SET ARRAY REPRESENTING M CLASSES INTO WHICH THE N ELEMENTS ARE DEVIDED -------
//---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
//---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
//---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------

float Fuzzyfication::febfc_step_4_compute_total_fuzzy_entropy(unsigned int attr) 
{
	//1) Let X = {r1, ... , rn} be a universal set with elements ri distributed in pattern space where i = 1..n. 
	//2) Let A be a fuzzy set defined on a interval of pattern space which kontains k elements (k < n). 

	//classes 
	float ***mu, **sum_mu;
	unsigned long* count_m;
	count_m = static_cast<unsigned long*>(newUnLong(Intervals[attr], 0L, "countM in EntropyCalc()"));

	mu = (float***) new float**[Intervals[attr]];
	sum_mu = (float**) new float*[Intervals[attr]];

	if (!mu || !sum_mu) MyError("Error allocation of (M and sumM) in febfc_step_4_compute_total_fuzzy_entropy()");
	//---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
		initialization_mu_function(attr, sum_mu, mu);
	//---------------------------II.C.----STEP 2 - SET FUZZY SET A CONTAINS K ELEMENTS ---------------------------
	//---------------------------II.C.----STEP 3 - SET ARRAY REPRESENTING M CLASSES INTO WHICH THE N ELEMENTS ARE DEVIDED -------
	//---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
	compute_mu_function(attr, count_m, mu);
	//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
	// Wage Degree Calculation
	compute_wage_degree_calculation(attr, sum_mu, mu);

	print_to_log_file_classes(attr, count_m);

	//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
	//---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
	//---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
	//  Fuzzy Entropy Calculation
	// The fuzzy entropy FE on the universal uset X for the elements within an interval 
	float total_fuzzy_entropy = 0.0f;
	compute_total_fuzzy_entropy(attr, total_fuzzy_entropy, count_m, sum_mu, mu);

	// delete M and sumM
	dealocate_pointers_entropy(attr, count_m, mu, sum_mu);

	return total_fuzzy_entropy;
}


void Fuzzyfication::initialization_mu_function(unsigned attr, float** sum_mu, float*** mu) 
{

	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
	{
		//initialization of sum
		sum_mu[class_m] = (float*)(newFloat(Intervals[attr], 0, "sumM(EntropyCalc)"));
		//initialization of mu function 
		mu[class_m] = (float**)(new float*[Intervals[attr]]);

		if (!mu[class_m])
		{
			MyError("Error allocation of (M[sector]) in EntropyCalcululate()");
		}
		//initialization of mu function for class 
		for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
		{
			//---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
			mu[class_m][j_a] = static_cast<float*>(newFloat(OutputIntervals, 0, "M in EntropyCalc()"));
		}
		//TODO DELETE []
	}
}

void Fuzzyfication::compute_wage_degree_calculation(unsigned attr, float** sum_mu, float*** mu) 
{
	//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
		for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
			for (unsigned int j_b = 0; j_b < OutputIntervals; j_b++)
				sum_mu[class_m][j_a] += mu[class_m][j_a][j_b];
}

void Fuzzyfication::compute_mu_function(unsigned attr, unsigned long* count_m, float*** mu) 
{
	float max = 0.0f;
	unsigned int class_m = 0;

	for (unsigned long data_item = 0; data_item < DatasetSize; data_item++)
	{
		max = FuzzySetOnInterval[attr][0][data_item];
		//SCJ - set of elements of class j on the universal set X. 
		//It is a subset of the universal X. 
		//---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
		set_scj_on_universal_set_x(attr, class_m, max, data_item);

		count_m[class_m]++;

		// Membership Degree Calculation
		match_degree_calculation(attr, class_m, mu, data_item);
	}
}

void Fuzzyfication::match_degree_calculation(unsigned attr, unsigned class_m, float*** mu, unsigned long data_item) 
{
	for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
	{
		for (unsigned int j_b = 0; j_b < OutputIntervals; j_b++)
		{
			mu[class_m][j_a][j_b] += FuzzySetOnInterval[attr][j_a][data_item] * FuzzySetOnInterval[InputAttributes][j_b][data_item];
		}
	}
}

void Fuzzyfication::set_scj_on_universal_set_x(unsigned attr, unsigned& class_m, float& max, unsigned long data_item) 
{
	//---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
	for (unsigned int j = 0; j < Intervals[attr]; j++)
	{
		if (max <= FuzzySetOnInterval[attr][j][data_item])
		{
			class_m = j;
			max = FuzzySetOnInterval[attr][j][data_item];
		}
	}
}


void Fuzzyfication::print_to_log_file_classes(unsigned attr, unsigned long* count_m) 
{
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
		fprintf(LogFile, "Members in cluster %d :\t %d \n", class_m, count_m[class_m]);
}

void Fuzzyfication::compute_total_fuzzy_entropy(unsigned attr, float& total_fuzzy_entropy,unsigned long* count_m, float** sum_mu, float*** mu ) 
{
	float new_entropy = 0.0f;
	float match_degree_d_j = 0.0f;
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
	{
		new_entropy = 0.0;
		for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
			for (unsigned int j_b = 0; j_b < OutputIntervals; j_b++)
			{
				//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
				if (static_cast<float>(sum_mu[class_m][j_a] == 0))
				{
					match_degree_d_j = 0;
				}
				else
				{
					match_degree_d_j = (mu[class_m][j_a][j_b] / sum_mu[class_m][j_a]);
				}

				//---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
				if (!(mu[class_m][j_a][j_b] == 0))
				{
					new_entropy -= match_degree_d_j * log2(match_degree_d_j);
				}
				//	fprintf(LogFile, "dimension=%d, jb=%d, p=%f New Entropy =%f\n", class_m, jb, p, new_entropy);
			}

		//---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
		total_fuzzy_entropy += new_entropy * static_cast<float>(count_m[class_m]) / DatasetSize;
	}
}

void Fuzzyfication::dealocate_pointers_entropy(unsigned attr, unsigned long* count_m, float*** mu, float** sum_mu) 
{
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
	{
		for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
			delete[] mu[class_m][j_a];
		delete[] mu[class_m];
		delete[] sum_mu[class_m];
	}
	delete[] mu;
	delete[] sum_mu;
	delete[] count_m;
}
