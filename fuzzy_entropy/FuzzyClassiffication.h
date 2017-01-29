#pragma once
#include "IDataset.h"
#include "KMeans.h"
#include "FloatLog.h"

struct FuzzyClassifficationInit
{
	unsigned int centers_count;
	float learning_rate;
	unsigned int class_count;
};

class FuzzyClassiffication
{
	private:
		class KMeans *kmeans;
		class IDataset *dataset;
		struct FuzzyClassifficationInit init_struct;

		std::vector<float> match_degree;
		std::vector<unsigned int> scj;

	private:
		class CFloatLog *result_log;

public:
	FuzzyClassiffication(class IDataset *dataset, struct FuzzyClassifficationInit init_struct);
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

