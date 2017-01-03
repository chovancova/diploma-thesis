#include "FuzzyClassiffication.h"


FuzzyClassiffication::FuzzyClassiffication(IDataset* dataset, FuzzyClassifficationInit init_struct)
{
	this->dataset = dataset;
	this->init_struct = init_struct;

	DetermineNumberOfIntervals();
}

FuzzyClassiffication::~FuzzyClassiffication()
{
	if (kmeans != nullptr)
	{
		delete kmeans;
		kmeans = nullptr;
	}
}

void FuzzyClassiffication::DetermineNumberOfIntervals()
{
	unsigned int centers_count_max = 10;
	for (unsigned int centers_count = 2; centers_count < centers_count_max; centers_count++)
	{
		//create new kmeans
		kmeans = new KMeans(centers_count, dataset->getFeatureSize());

		//train kmeans using dataset
		trainKMeans();

		//zratanie entropie
		float entropy = computeEntropy();


		//if (nie je zloepsnie)
		//delete kmeans;




		for (unsigned idx = 0; idx < dataset->getSize(); idx++)
		{
			kmeans->process(dataset->get(idx), 0.0);

			dataset->print(idx);
			kmeans->print_result();
			printf("\n");
		}
	}
}


void FuzzyClassiffication::trainKMeans()
{
	//init centers from dataset
	for (unsigned int i = 0; i < kmeans->getSize(); i++)
	{
		DataItem item;
		item = dataset->rndFromArray();
		kmeans->setCenter(item, i);
	}

	unsigned int iterations = 0, iterations_max = 100000;

	float k = 0.1;
	float center_difference = 1.0;

	//unsupervised k-means learning
	do
	{
		DataItem item;
		item = dataset->rndFromArray();
		float center_difference_tmp = kmeans->process(item, init_struct.learning_rate);

		center_difference = (1.0 - k)*center_difference + k*center_difference_tmp;

		iterations++;
	} while ((center_difference > 0.0001) && (iterations < iterations_max));

	// printf("iterations %u diff %f\n", iterations, center_difference);
}

float FuzzyClassiffication::computeEntropy()
{
	return 0;
}
