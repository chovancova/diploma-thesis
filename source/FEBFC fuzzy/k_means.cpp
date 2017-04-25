#include "k_means.h"


CKameans::CKameans(unsigned int centers_count, unsigned int inputs_count, unsigned int outputs_count)
{
	for (unsigned int i = 0; i < centers_count; i++)
	{
		struct sKmeansItem item;

		for (unsigned int j = 0; j < inputs_count; j++)
		{
			float tmp = ((2.0*i) / centers_count - 1.0) / 2.0;
			item.input.push_back(tmp);
		}

		for (unsigned int j = 0; j < outputs_count; j++)
			item.output.push_back(0.0);

		centers.push_back(item);
	}

	used_centers = 0;
}

CKameans::~CKameans()
{

}

void CKameans::train(std::vector<float> &input, std::vector<float> &required_output)
{
	unsigned int nearest = 0;
	float dist_min = input.size()*10000.0;

	float eta = 0.01;         //learning rate

							  //find nearest center
	for (unsigned int j = 0; j < centers.size(); j++)
	{
		float dist = distance(centers[j].input, input);
		if (dist < dist_min)
		{
			dist_min = dist;
			nearest = j;
		}
	}

	//move nearest center
	for (unsigned int i = 0; i < centers[nearest].input.size(); i++)
		centers[nearest].input[i] = (1.0 - eta)*centers[nearest].input[i] + eta*input[i];

	//move nearest data
	for (unsigned int i = 0; i < centers[nearest].output.size(); i++)
		centers[nearest].output[i] = (1.0 - eta)*centers[nearest].output[i] + eta*required_output[i];

	for (unsigned int j = 0; j < centers.size(); j++)
		if (j != nearest)
		{
			float eta_ = 0.1*eta;
			for (unsigned int i = 0; i < centers[j].input.size(); i++)
				centers[j].input[i] = (1.0 - eta_)*centers[j].input[i] + -eta_*input[i];
		}


	//avoid colision with near
	for (unsigned int j = 0; j < centers.size(); j++)
		if (j != nearest)
			if (distance(centers[j].input, centers[nearest].input) < 0.1)
			{
				for (unsigned int i = 0; i < centers[j].input.size(); i++)
					centers[j].input[i] = rnd();
			}
}

unsigned int CKameans::process(std::vector<float> &input)
{
	unsigned int nearest = 0;
	float dist_min = input.size()*10000.0;

	//find nearest center
	for (unsigned int j = 0; j < centers.size(); j++)
	{
		float dist = distance(centers[j].input, input);
		if (dist < dist_min)
		{
			dist_min = dist;
			nearest = j;
		}
	}

	return nearest;
}


float CKameans::distance(std::vector<float> &a, std::vector<float> &b)
{
	float sum = 0.0;

	for (unsigned int i = 0; i < a.size(); i++)
	{
		sum += (a[i] - b[i])*(a[i] - b[i]);
	}

	return sqrt(sum) / a.size();
}


float CKameans::rnd()
{
	return ((rand() % 20000000) / 10000000.0) - 1.0;
}
