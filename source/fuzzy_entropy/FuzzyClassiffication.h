#pragma once
#include "Dataset.h"
#include "KMeans.h"
#include "FloatLog.h"

class Dataset;

struct FuzzyClassifficationInit
{
	unsigned int centers_count;
	float learning_rate;
	unsigned int class_count;
};

class FuzzyClassiffication
{
	private:
		KMeans *kmeans;
		Dataset *dataset;
		FuzzyClassifficationInit init_struct;

		std::vector<float> match_degree;
		std::vector<unsigned int> scj;

	private:
		class Logger *result_log;

public:
	FuzzyClassiffication(Dataset *dataset, FuzzyClassifficationInit init_struct);
	~FuzzyClassiffication();

private:
	void DetermineNumberOfIntervals();
	void ProcessClassification(unsigned centers_count);
	void trainKMeans();
	float computeEntropy();

	float compute_fuzzy_entropy();
	float compute_fuzzy_entropy_of_interval(unsigned cluster_id);
	std::vector<struct DataItem> generate_scj(unsigned int class_index);

};

