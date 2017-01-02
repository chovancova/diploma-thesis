#include "KMeans.h"



KMeans::KMeans(unsigned int centers_count, unsigned int features_count)
{
	for (unsigned int j = 0; j < centers_count; j++)
	{
		struct DataItem tmp;
		tmp.label = 0;

		for (unsigned int i = 0; i < features_count; i++)
			tmp.features_normalised.push_back(rnd());
		centers.push_back(tmp);
	}

	for (unsigned int i = 0; i < centers_count; i++)
		result.distances.push_back(0.0f);

	result.cluster_id = 0;
	result.label = 0.0;
}


KMeans::~KMeans()
{

}

void KMeans::process(struct DataItem &item, float learning_rate)
{
	for (unsigned int i = 0; i < centers.size(); i++)
		result.distances[i] = distance(centers[i].features_normalised, item.features_normalised);


	unsigned int min_idx = 0;
	for (unsigned int i = 0; i < centers.size(); i++)
	{
		if (result.distances[i] < result.distances[min_idx])
			min_idx = i;
	}

	result.cluster_id = min_idx;
	result.label = centers[min_idx].label;

	for (unsigned int i = 0; i < centers[min_idx].features_normalised.size(); i++)
	{
		centers[min_idx].features_normalised[i] = (1.0f - learning_rate)*centers[min_idx].features_normalised[i] 
												+ learning_rate*item.features_normalised[i];
	
	}

	centers[min_idx].label = (1.0f - learning_rate)*centers[min_idx].label + learning_rate*item.label;

}


struct KMeansResult KMeans::get()
{
	return result;
}

unsigned int KMeans::getSize()
{
	return centers.size();
}

struct DataItem KMeans::get_center(unsigned int index)
{
	return centers[index];
}

void KMeans::print_result()
{
	printf("cluster id %i label %6.3f :", result.cluster_id, result.label);
	for (unsigned int i = 0; i < result.distances.size(); i++)
		printf("%6.3f ", result.distances[i]);

	printf("\n");
}



float KMeans::distance(std::vector<float> &v1, std::vector<float> &v2)
{
	if (v1.size() != v2.size())
	{
		return -1.0;
	}

	float sum = 0.0;
	for (unsigned int i = 0; i < v1.size(); i++)
	{
		sum += (v1[i] - v2[i])*(v1[i] - v2[i]);
	}

	return sqrt(sum);
}

float KMeans::rnd()
{
	float temp = ((rand()% 20000) / 10000.0f) - 1.0;
	return temp;
}