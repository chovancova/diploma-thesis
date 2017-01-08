#include "MembershipFunction.h"


MembershipFunction::MembershipFunction(KMeans* kmeans)
{
	this->kmeans = kmeans;

	for (unsigned int i = 0; i < kmeans->getSize(); i++)
	{
		struct DataItem item = kmeans->get_center(i);
		centers.push_back(item.features_normalised);
	}

	for (unsigned int i = 0; i <  centers.size(); i++)
	{
		std::vector<float> tmp(centers[i].size(), 0.0f);
		result.push_back(tmp);
	}
}

MembershipFunction::~MembershipFunction()
{
}

void MembershipFunction::process(std::vector<float> input)
{
	for (unsigned int center = 0; center < centers.size(); center++)
	{
		for (unsigned int dimension = 0; dimension < centers[center].size(); dimension++)
		{
			int left_c = get_left_center(center, dimension);
			int right_c = get_right_center(center, dimension);
			result[center][dimension] = mu(input[dimension], center, left_c, right_c, dimension);
		}
	}
	// float MembershipFunction::mu(float x, int c, int c_left, int c_right, unsigned int dimension)

}

std::vector<std::vector<float>> MembershipFunction::get()
{
	return result;
}

void MembershipFunction::print()
{
	for (unsigned int center = 0; center < result.size(); center++)
	{
		for (unsigned int dimension = 0; dimension < result[center].size(); dimension++)
			printf("%6.3f ", result[center][dimension]);
		
		/*
		printf(" : ");

		struct DataItem item = kmeans->get_center(center);
		for (unsigned int i = 0; i < item.features_normalised.size(); i++)
			printf("%6.3f ", item.features_normalised[i]);
		printf("\n");
*/
	}		

	printf("\n");

}


float MembershipFunction::mu(float x, int c, int c_left, int c_right, unsigned int dimension)
{
	float result = 0.0f;

	// most left case
	if (c_left < 0)
	{
		if (x <= centers[c][dimension])
			result = (x + centers[c][dimension] + 2.0f) / (2.0f*centers[c][dimension] + 2.0f);
		else
		{
			float tmp = 1.0f - abs(x - centers[c][dimension]) / abs(centers[c_right][dimension] - centers[c][dimension]);
			result = max(0.0f, tmp);
		}
	}
	// most right case
	else if (c_right < 0)
	{
		if (x <= centers[c][dimension])
		{
			float tmp = 1.0f - abs(centers[c][dimension] - x) / abs(centers[c][dimension] - centers[c_left][dimension]);
			result = max(0.0f, tmp);
		}
		else
			result = (2.0f - x - centers[c][dimension]) / (2.0f - 2.0f*centers[c][dimension]);
	}
	// internal case
	else 
	{
		if (x <= centers[c][dimension])
		{
			float tmp = 1.0f - abs(centers[c][dimension] - x) / abs(centers[c][dimension] - centers[c_left][dimension]);
			result = max(0.0f, tmp);
		}
		else
		{
			float tmp = 1.0f - abs(x - centers[c][dimension]) / abs(centers[c_right][dimension] - centers[c][dimension]);
			result = max(0.0f, tmp);
		}
	}

	return result;
}

int MembershipFunction::get_left_center(int center_index, unsigned int dimension)
{
	int result = -1;

	float distance_min = 1000000.0f;

	for (unsigned int i = 0; i < centers.size(); i++)
	{
		if (i != center_index)
		{
			float distance = centers[center_index][dimension] - centers[i][dimension];
			if (distance > 0.0f)
			
				if (distance < distance_min)
				{
					distance_min = distance;
					result = i;
				}
		}
	}
	return  result;
}

int MembershipFunction::get_right_center(int center_index, unsigned int dimension)
{
	int result = -1;

	float distance_min = 1000000.0f;

	for (unsigned int i = 0; i < centers.size(); i++)
	{
		if (i != center_index)
		{
			float distance = centers[i][dimension] - centers[center_index][dimension];

			if (distance > 0.0f)
				if (distance < distance_min)
				{
					distance_min = distance;
					result = i;
				}
		}
	}
	return  result;
}

float MembershipFunction::max(float a, float b)
{
	if (a > b)
		return a;
	return b;
}
