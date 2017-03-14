#define EPSILON 0.00001f
#include <complex.h>
#include <cmath>
#include <cstdio>
#include "Fuzzyfication.h"
#include "TempFunctions.h"
#include <iterator>

float Fuzzyfication::ComputeDistance(float a, float b, int type_distance, int p) const
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

//FCM is one of the most popular fuzzy clustering techniques, which was proposed by
//Dunn[8] in 1973 and eventually modified by Bezdek[4] in 1981. It is an approach,
//where the data points have their membership values with the cluster centers, which
//will be updated iteratively.The FCM algorithm consists of the following steps :
//
//Step 1 : Let us suppose that M - dimensional N data points represented by xi
//(i = 1, 2, . . ., N), are to be clustered.
//
//Step 2 : Assume the number of clusters to be made, that is, C, where 2 ≤ C ≤ N.
//
//Step 3 : Choose an appropriate level of cluster fuzziness f > 1.
//
//Step 4: Initialize the N × C × M sized membership matrix U, at random, such
//that Uijm in [0, 1] and PC
//j = 1 Uijm = 1.0, for each i and a fixed value of m.
//
//Step 5 : Determine the cluster centers CCjm, for j
//th cluster and its mth dimension
//by using the expression given below :
//CCjm = sum(i in all N) U(f _ ijm) x(_im) / sum(i in N) U(f, ijm)
//
//Step 6 : Calculate the Euclidean distance between i
//th data point and j
//th cluster
//center with respect to, say mth dimension like the following :
//Dijm = k(xim − CCjm)k.
float* Fuzzyfication::CenterFuzzy(unsigned int attribute, unsigned int NumberOfCenters, float m, unsigned int distance_type) const
{
	double temp;
	double temp1;
	double temp2;
	float** membership_function;
	float* centers;
	unsigned int intervals;//Number Of Intervals
	intervals = NumberOfCenters;

	centers = static_cast<float*>(newFloat(intervals, 0.0, "CenterFuzzy "));
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

	float current = 0;
	float last;
	float different; // current - last
	float part;
	float min = 0.0;
	float max = 1.0;

	part = (max - min) / intervals * 1.0f;

	for (unsigned int i = 0; i < intervals; i++)
	{
		centers[i] = min + (i * part);
	}

	different = EPSILON + 1.0f;

	while ((different >= EPSILON) && (t <= LIMIT_ITTERATION))
	{
		for (unsigned long k = 0; k < DatasetSize; k++)
		{
			assigned[k] = false;
		}

		t++;
		last = current;
		//number of clusters 
		for (unsigned int i = 0; i < intervals; i++)
		{
			for (unsigned long dataset_item = 0; dataset_item < DatasetSize; dataset_item++)
			{
				temp = 0;
				for (unsigned int interval = 0; interval < intervals; interval++)
					if (assigned[dataset_item] == false)
					{
						float distanceI = ComputeDistance(Features[dataset_item].Dimension[attribute], centers[i], distance_type, 4);
						float distanceJ = ComputeDistance(Features[dataset_item].Dimension[attribute], centers[interval], distance_type, 4);

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
		// Computing  new center for every cluster
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

		current = 0;
		for (unsigned int i = 0; i < intervals; i++)
			for (unsigned long k = 0; k < DatasetSize; k++)
			{
				float distanceNew = ComputeDistance(Features[k].Dimension[attribute], centers[i], distance_type, 4);

				current += pow(membership_function[i][k], m) * pow(distanceNew, 2);
			}

		if (t > 1) different = fabs(current - last);
	}

	for (unsigned int i = 0; i < intervals; i++)
	{
		delete[] membership_function[i];
	}
	delete[] membership_function;
	return centers;
}


float* Fuzzyfication::Center(unsigned int i, float* Result, unsigned long* NewResult, unsigned long countResult) const
{
	unsigned int q; //cluster
	unsigned int* total_patterns; //Nq is total number of patterns within the same cluster q. 
	unsigned int distance_n = 0;
	bool stop;
	unsigned int z;
	unsigned int iteration;
	float *c, *sum, center, distance;

	c = static_cast<float*>(new float[Intervals[i]]);
	c = static_cast<float*>(CenterFuzzy(i, Intervals[i], 2.0f, 3));
	for (z = 0; z < Intervals[i]; z++) fprintf(LogFile, "cluster[%d]=%f ", z, c[z]);
	fprintf(LogFile, "\n");

	iteration = 0;
	do //**********************************************************
	{
		sum = newFloat(Intervals[i], 0.0, "sum in Center()");
		total_patterns = newUnInt(Intervals[i], 0, "Nq  in Center()");
		for (unsigned long k = 0; k < countResult; k++)
		{
			distance = fabs(Result[k] - c[0]);
			for (q = 0; q < Intervals[i]; q++) // minimal ComputeDistance calculate
				if (distance >= fabs(Result[k] - c[q]))
				{
					distance = fabs(Result[k] - c[q]);
					distance_n = q;
				}
			sum[distance_n] += Result[k] * NewResult[k];
			total_patterns[distance_n] += NewResult[k];
		}

		stop = false;
		for (q = 0; q < Intervals[i]; q++) // end of clastering
		{
			if (total_patterns == 0)
			{
				MyError("not possible situation: Nq[q]=0 in Center()");
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
		//Check - not same cluster centers
		for (q = 0; q < Intervals[i] - 1; q++)
		{
			if (c[q] == c[q + 1])
			{
				MyError("UnReal situation: c[q]=c[q+1] in Center()");
			}
		}
		delete[] sum;
		delete[] total_patterns;
	}
	while ((stop) && (iteration < LIMIT_ITTERATION));


	SortAscendingOrder(c, Intervals[i]);

	for (z = 0; z < Intervals[i]; z++)fprintf(LogFile, "c__2[%d]=%f ", z, c[z]);
	fprintf(LogFile, "\n");
	return (c);
}
