#include "fuzzy_entropy.h"


CFuzzyEntropy::CFuzzyEntropy()
{

}

CFuzzyEntropy::~CFuzzyEntropy()
{

}


struct sFuzzyEntropyResult CFuzzyEntropy::process(unsigned int attribute_id, class CKameans &kmeans, class CDatasetInterface *dataset)
{
	std::vector<std::vector<float>> membership_degree;

	unsigned int classes_count = dataset->get_output_size();
	unsigned int clusters_count = kmeans.centers.size();

	//initialize membership degree to 0.0
	for (unsigned int j = 0; j < classes_count; j++)
	{
		std::vector<float> tmp;
		for (unsigned int i = 0; i < clusters_count; i++)
			tmp.push_back(0.0);

		membership_degree.push_back(tmp);
	}

	//create membership function with i-th cluster as center

	std::vector<float> centers;

	for (unsigned int j = 0; j < kmeans.centers.size(); j++)
		centers.push_back(kmeans.centers[j].input[attribute_id]);

	struct sFuzzyEntropyResult result;
	result.membership_function = CMembershipFunction(centers);
	result.entropy = 1.0;



	//computer fuzzy entropy
	//for all classes
	for (unsigned int j = 0; j < classes_count; j++)
	{
		//create subset with only j-th class from dataset
		std::vector<struct sDatasetItem> scj = make_subset(j, dataset);

		for (unsigned int i = 0; i < clusters_count; i++)
		{
			float sum = 0.0;
			for (unsigned int k = 0; k < scj.size(); k++)
			{
				//fill k-means tmp input with only one attribute
				std::vector<float> tmp;
				tmp.push_back(scj[k].input[attribute_id]);

				//only if k-th item is in i-th cluster
				if (kmeans.process(tmp) == i)
				{
					result.membership_function.process(scj[k].input[attribute_id]);
					sum += result.membership_function.result[i];
				}
			}

			membership_degree[j][i] = sum;
		}
	}

	/*
	for (unsigned int j = 0; j < membership_degree.size(); j++)
	{
	for (unsigned int i = 0; i < membership_degree[j].size(); i++)
	printf("%6.3f ", membership_degree[j][i]);
	printf("\n");
	}
	printf("\n");
	*/


	std::vector<float> entropy_result;
	for (unsigned int i = 0; i < clusters_count; i++)
	{
		float sum = 0.0;
		for (unsigned int j = 0; j < classes_count; j++)
			sum += membership_degree[j][i];

		float d = 0.0;
		//equation P2
		for (unsigned int j = 0; j < classes_count; j++)
		{
			float dj = membership_degree[j][i] / sum; //equation P3

			if (dj > 0.0)
				d += -dj*log2(dj);
		}

		entropy_result.push_back(d);
	}


	//equation P1
	result.entropy = 0.0;
	for (unsigned int i = 0; i < entropy_result.size(); i++)
		result.entropy += entropy_result[i];

	return result;
}

float CFuzzyEntropy::get()
{
	return result;
}


std::vector<struct sDatasetItem> CFuzzyEntropy::make_subset(unsigned int class_id, class CDatasetInterface *dataset)
{
	std::vector<struct sDatasetItem> result;

	for (unsigned int i = 0; i < dataset->get_size(); i++)
	{
		struct sDatasetItem item = dataset->get(i);
		if (item.output[class_id] > 0.0)
			result.push_back(item);
	}

	return result;
}
