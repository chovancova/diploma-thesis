#pragma once
#include "IDataset.h"
#include "KMeans.h"

struct FuzzyClassifficationInit
{
	unsigned int centers_count;
	float learning_rate;
};

class FuzzyClassiffication
{
	private:
		class KMeans *kmeans;
		class IDataset *dataset;
		struct FuzzyClassifficationInit init_struct;

public:
	FuzzyClassiffication(class IDataset *dataset, struct FuzzyClassifficationInit init_struct);
	~FuzzyClassiffication();
private:
	void DetermineNumberOfIntervals();
	void trainKMeans();
	float computeEntropy();
};

