#include "MembershipFunction.h"


MembershipFunction::MembershipFunction(KMeans* kmeans)
{
	for (unsigned int i = 0; i < kmeans->getSize(); i++)
	{
		struct DataItem item = kmeans->get_center(i);
		centers.push_back(item.features_normalised);
	}

	for (unsigned int i = 0; i <  kmeans->getSize(); i++)
	{
		std::vector<float> tmp(kmeans->getSize(), 0.0f);
		result.push_back(tmp);
	}
}

MembershipFunction::~MembershipFunction()
{
}

void MembershipFunction::process(std::vector<float> input)
{
	for (unsigned int i = 0; i < centers.size(); i++)
	{
		for (unsigned int j = 0; j < input.size(); j++)
			result[i][j] = mu(input[j], c, c_left, c_right);

	}
}

std::vector<std::vector<float>> MembershipFunction::get()
{
	return result;
}

float MembershipFunction::mu(float x, float c, float c_left, float c_right)
{

}
