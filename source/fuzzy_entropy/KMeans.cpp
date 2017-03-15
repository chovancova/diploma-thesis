#include "KMeans.h"



KMeans::KMeans(unsigned int centers_count, unsigned int features_count, unsigned int classes_count)
{
	for (unsigned int j = 0; j < centers_count; j++)
	{
		struct DataItem tmp;

		for (unsigned int i = 0; i < classes_count; i++)
			tmp.label.push_back(0.0);

		for (unsigned int i = 0; i < features_count; i++)
			tmp.features_normalised.push_back(rnd());
		centers.push_back(tmp);
	}

	for (unsigned int i = 0; i < centers_count; i++)
		result.distances.push_back(0.0f);

	result.cluster_id = 0;
}


KMeans::~KMeans()
{

}

float KMeans::process(struct DataItem &item, float learning_rate)
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

	//normalise result label
	float sum = 0.0;
	for (unsigned int i = 0; i < result.label.size(); i++)
		sum += result.label[i];

	for (unsigned int i = 0; i < result.label.size(); i++)
		result.label[i] /= sum;

	float center_difference = 0.0;

	if (learning_rate > 0.0)
	{
		//kohonen network = in the future move not only center[min_idx], but all generally move all other 
		for (unsigned int i = 0; i < centers[min_idx].features_normalised.size(); i++)
		{
			float tmp = centers[min_idx].features_normalised[i];
			centers[min_idx].features_normalised[i] = (1.0f - learning_rate)*centers[min_idx].features_normalised[i]
				+ learning_rate*item.features_normalised[i];
			
			//avoid very very similar centers[min_idx] -> if centers[min_idx] == centers[i], set centers[min_idx] random
			//okolo centra zasumi do vzdialenosti ...
			for (unsigned int k = 0; k < centers.size(); k++)
				if (k != min_idx)
				{
					float eta = 0.5;//sum
					float tmp2 = centers[min_idx].features_normalised[i] - centers[k].features_normalised[i];
					if (abs(tmp2) < 0.001)
					{
						centers[min_idx].features_normalised[i] = (1.0 - eta)*centers[min_idx].features_normalised[i] + eta*rnd();
					}
				}


			center_difference += (centers[min_idx].features_normalised[i] - tmp)*(centers[min_idx].features_normalised[i] - tmp);
		}

		for (unsigned int i = 0; i < centers[min_idx].label.size(); i++)
			centers[min_idx].label[i] = 
				(1.0f - learning_rate)*centers[min_idx].label[i] + learning_rate*item.label[i];

		center_difference = sqrt(center_difference);
	}

	return center_difference;
}


struct KMeansResult KMeans::get()
{
	return result;
}

unsigned int KMeans::getSize()
{
	return centers.size();
}


unsigned int KMeans::getCenterItemSize()
{
	return centers[0].features_normalised.size();
}

void KMeans::setCenter(struct DataItem center, unsigned int index)
{
	if(index < centers.size())
	{
			centers[index] = center;
	}
}

struct DataItem KMeans::get_center(unsigned int index)
{
	return centers[index];
}

void KMeans::print_result()
{
	printf("cluster id %i ", result.cluster_id);
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

