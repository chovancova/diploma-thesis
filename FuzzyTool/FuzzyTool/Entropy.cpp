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
	std::vector<unsigned long> count_m;
	count_m = std::vector<unsigned long>(Intervals[attr], 0L);

	//---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
		std::vector<std::vector<float>> sum_mu = std::vector<std::vector<float>>(Intervals[attr], std::vector<float>(Intervals[attr], 0.0));
		std::vector<std::vector<std::vector<float>>> mu = std::vector<std::vector<std::vector<float>>>(Intervals[attr], std::vector<std::vector<float>>(Intervals[attr], std::vector<float>(OutputIntervals, 0.0)));

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


void Fuzzyfication::compute_wage_degree_calculation(unsigned attr, std::vector<std::vector<float>>& sum_mu, std::vector<std::vector<std::vector<float>>>& mu)
{
	//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
		for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
			for (unsigned int j_b = 0; j_b < OutputIntervals; j_b++)
				sum_mu[class_m][j_a] += mu[class_m][j_a][j_b];
}

void Fuzzyfication::compute_mu_function(unsigned attr, std::vector<unsigned long>& count_m, std::vector<std::vector<std::vector<float>>>& mu)
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

void Fuzzyfication::match_degree_calculation(unsigned attr, unsigned class_m, std::vector<std::vector<std::vector<float>>>& mu, unsigned long& data_item)
{
	for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
	{
		for (unsigned int j_b = 0; j_b < OutputIntervals; j_b++)
		{
			mu[class_m][j_a][j_b] += FuzzySetOnInterval[attr][j_a][data_item] * FuzzySetOnInterval[InputAttributes][j_b][data_item];
		}
	}
}

void Fuzzyfication::set_scj_on_universal_set_x(unsigned attr, unsigned& class_m, float& max, unsigned long& data_item)
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


void Fuzzyfication::print_to_log_file_classes(unsigned attr, std::vector<unsigned long> count_m) 
{
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
		fprintf(LogFile, "Members in cluster %d :\t %d \n", class_m, count_m[class_m]);
}

void Fuzzyfication::compute_total_fuzzy_entropy(unsigned attr, float& total_fuzzy_entropy,std::vector<unsigned long> count_m, std::vector<std::vector<float>> &sum_mu, std::vector<std::vector<std::vector<float>>>& mu )
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

void Fuzzyfication::dealocate_pointers_entropy(unsigned attr, std::vector<unsigned long> &count_m, std::vector<std::vector<std::vector<float>>>& mu, std::vector<std::vector<float>>& sum_mu)
{
		mu.clear();
		sum_mu.clear();
		count_m.clear();
}
