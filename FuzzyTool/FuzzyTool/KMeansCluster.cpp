#define EPSILON 0.00001f
#include <complex.h>
#include <cmath>
#include <cstdio>
#include "Fuzzyfication.h"
#include "TempFunctions.h"
#include <iterator>

float Fuzzyfication::compute_distance(float a, float b, int type_distance, int p) const
{
	switch (type_distance)
	{
	case 1:
		{
			return sqrt((a - b) * (a - b));//Euklid
		}
	case 2:
		{
			return (a - b) * (a - b); //Euklid quadratic
		}
	case 3:
		{
			return fabs(a - b); //Mancheten
		}
	case 4:
		{
			return pow(pow((a - b), p), (1 / p)); //Minkowski
		}
	default:
		{
			return sqrt((a - b) * (a - b)); //Euklid
		}
	}
}

float* Fuzzyfication::fuzzy_clustering_fcm(unsigned int attribute, unsigned int NumberOfCenters, float m, unsigned int distance_type) const
{
	double temp;
	double temp1;
	double temp2;
	float** membership_function;
	float* centers;
	unsigned int intervals;//Number Of Intervals
	intervals = NumberOfCenters;
	//-------------------------------STEP 1-------------------------------------------
	//Step 1 : Let us suppose that M - dimensional N data points represented by xi (i = 1, 2, . . ., N), are to be clustered.
	centers = static_cast<float*>(newFloat(intervals, 0.0, "fuzzy_clustering_fcm "));
	membership_function = static_cast<float**>(new float*[intervals]);

	if (!membership_function)
	{
		printf("Error allocation - **MembershipFunction");
	}

	for (unsigned int interval = 0; interval < intervals; interval++)
	{
		membership_function[interval] = static_cast<float*>(newFloat(DatasetSize, 0.0, "MembershipFunction[interval] "));
	}
	//-------------------------------------------------------
	int t = 0;
	bool* assigned;
	assigned = new bool[DatasetSize];

	float current_cluster = 0;
	float last_cluster;
	float difference_coefficient; // current - last
	float min = 0.0;
	float max = 1.0;

	float part = (max - min) / intervals * 1.0f;

	for (unsigned int i = 0; i < intervals; i++)
	{
		centers[i] = min + (i * part);
	}

	difference_coefficient = EPSILON + 1.0f;

	while ((difference_coefficient >= EPSILON) && (t <= LIMIT_ITTERATION))
	{
		for (unsigned long k = 0; k < DatasetSize; k++)
		{
			assigned[k] = false;
		}
		t++;

		last_cluster = current_cluster;
		//number of clusters 
		for (unsigned int i = 0; i < intervals; i++)
		{
			for (unsigned long dataset_item = 0; dataset_item < DatasetSize; dataset_item++)
			{
				temp = 0;
				for (unsigned int interval = 0; interval < intervals; interval++)
					if (assigned[dataset_item] == false)
					{
						float distanceI = compute_distance(Features[dataset_item].Dimension[attribute], centers[i], distance_type, 4);
						float distanceJ = compute_distance(Features[dataset_item].Dimension[attribute], centers[interval], distance_type, 4);
					
						if (distanceI != 0 && distanceJ != 0)
						{
							temp += pow(distanceI / distanceJ, ((2 / (m - 1)) * 1.0f));
							membership_function[i][dataset_item] = (temp == 0) ? 1.0 : 1 / temp;
						}
						else if (distanceI == 0)
						{
							for (unsigned int l = 0; l < intervals; l++)
							{
								membership_function[l][dataset_item] = 0;
							}
							membership_function[i][dataset_item] = 1;
							assigned[dataset_item] = true;
						}
					}
			}
		}
		/////////////////////////////////////////////STEP 3////////////////////////////////////////////////
		// Computing  new febfc_step_2_locate_center_of_interval for every cluster
		for (unsigned int i = 0; i < intervals; i++)
		{
			temp1 = 0;
			temp2 = 0;
			for (unsigned long k = 0; k < DatasetSize; k++)
			{
				temp1 += pow(membership_function[i][k], m) * Features[k].Dimension[attribute];
				temp2 += pow(membership_function[i][k], m);
			}
			centers[i] = (temp2 == 0) ? 0 : temp1 / temp2;
		}

		current_cluster = 0;
		for (unsigned int i = 0; i < intervals; i++)
			for (unsigned long k = 0; k < DatasetSize; k++)
			{
				float distanceNew = compute_distance(Features[k].Dimension[attribute], centers[i], distance_type, 4);

				current_cluster += pow(membership_function[i][k], m) * pow(distanceNew, 2);
			}

		if (t > 1) difference_coefficient = fabs(current_cluster - last_cluster);
	}

	for (unsigned int i = 0; i < intervals; i++)
	{
		delete[] membership_function[i];
	}
	delete[] membership_function;
	return centers;
}

//---------------------------B.--DETERMINATION OF THE INTERVAL LOCATIONS---------------------------------------
//-------------------------------STEP 1 - INITIAL NUMBER OF CLUSTERS -------------------------------------------
//-------------------------------STEP 2 - INITIAL CENTERS OF CLUSTERS -------------------------------------------
//-------------------------------STEP 3 - ASSIGN CLUSTER LABEL TO EACH ELEMENT------------------------------------
//-------------------------------STEP 4 - RECOMPUTE THE CLUSTER CENTERS ------------------------------------
//-------------------------------STEP 5 - DOES ANY CENTER CHANGE ? ------------------------------------
float* Fuzzyfication::febfc_step_2_locate_center_of_interval(unsigned int i, float* Result, unsigned long* NewResult, unsigned long countResult) const
{
	unsigned int q; //cluster
	unsigned int* total_patterns; //Nq is total number of patterns within the same cluster q. 
	unsigned int distance_n = 0;
	bool stop;
	unsigned int z;
	unsigned int iteration;
	float *c, *sum, center, distance;

	//-------------------------------STEP 1- INITIAL NUMBER OF CLUSTERS -------------------------------------------
	iteration = 0;

	//-------------------------------STEP 2 - INITIAL CENTERS OF CLUSTERS -------------------------------------------
	c = static_cast<float*>(fuzzy_clustering_fcm(i, Intervals[i], 2.0f, 3));

	fprintf(LogFile, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	fprintf(LogFile, "Current cluster centers\n");
	print_to_log_file_clusters_interval_location(i, c);

	do
	{
		sum = newFloat(Intervals[i], 0.0, "sum in febfc_step_2_locate_center_of_interval()");
		total_patterns = newUnInt(Intervals[i], 0, "Nq  in febfc_step_2_locate_center_of_interval()");
		for (unsigned long k = 0; k < countResult; k++)
		{
			//-------------------------------STEP 3 - ASSIGN CLUSTER LABEL TO EACH ELEMENT------------------------------------
			distance = fabs(Result[k] - c[0]);
			for (q = 0; q < Intervals[i]; q++) // minimal compute_distance calculate
				if (distance >= fabs(Result[k] - c[q]))
				{
					distance = fabs(Result[k] - c[q]);
					distance_n = q;
				}
			sum[distance_n] += Result[k] * NewResult[k];

			total_patterns[distance_n] += NewResult[k];
		}

		stop = false;
		//-------------------------------STEP 4 - RECOMPUTE THE CLUSTER CENTERS ------------------------------------
		for (q = 0; q < Intervals[i]; q++) 
		{
			if (total_patterns == 0)
			{
				MyError("not possible situation: Nq[q]=0 in febfc_step_2_locate_center_of_interval()");
			}
			else
			{
				center = static_cast<float>(sum[q]) / static_cast<float>(total_patterns[q]);
				if (c[q] != center)
				{
					c[q] = center;
					stop = true;
				}
				iteration++;
			}
		}
		//-------------------------------STEP 5 - DOES ANY CENTER CHANGE ? ------------------------------------
		//Check - not same cluster centers
		for (q = 0; q < Intervals[i] - 1; q++)
		{
			if (c[q] == c[q + 1])
			{
				MyError("UnReal situation: c[q]=c[q+1] in febfc_step_2_locate_center_of_interval()");
			}
		}

		delete[] sum;
		delete[] total_patterns;
	}
	while ((stop) && (iteration < LIMIT_ITTERATION));
	

	sort_ascending_order(c, Intervals[i]);
	
	fprintf(LogFile, "New cluster centers\n");
	print_to_log_file_clusters_interval_location(i, c);

	return (c);
}



void Fuzzyfication::print_to_log_file_clusters_interval_location(unsigned i,  float* c) const
{
	for (unsigned z = 0; z < Intervals[i]; z++)
		fprintf(LogFile, "Cluster center [%d] location:\t\t%f\n", z, c[z]);

	fprintf(LogFile, "\n");
}
