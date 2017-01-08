#include "FuzzyClassiffication.h"
#include "MembershipFunction.h"


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
	unsigned int centers_count_max = 50;
	for (unsigned int centers_count = 2; centers_count < centers_count_max; centers_count++)
	{
		//create new kmeans
		kmeans = new KMeans(centers_count, dataset->getFeatureSize());

		//train kmeans using dataset
		trainKMeans();

		//zratanie entropie
		float entropy = computeEntropy();

		printf("entropy %f\n", entropy);

		//if (nie je zlepsneie)
		delete kmeans;
		kmeans = nullptr;



		/*
		for (unsigned idx = 0; idx < dataset->getSize(); idx++)
		{
			kmeans->process(dataset->get(idx), 0.0);

			dataset->print(idx);
			kmeans->print_result();
			printf("\n");
		}
		*/
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

	unsigned int iterations = 0, iterations_max = 10000;

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
	MembershipFunction *membership_function = new MembershipFunction(kmeans);
	
	std::vector<std::vector<std::vector<float>>> mu;

	for (unsigned int item_index = 0; item_index < dataset->getSize(); item_index++)
	{
		DataItem item;
		item = dataset->get(item_index);

		membership_function->process(item.features_normalised);

		mu.push_back(membership_function->get());
		
		if (item_index == 0)
			membership_function->print();
	}

	delete membership_function;

	float entropy = 0.0;

	for (unsigned int class_index = 0; class_index < kmeans->getSize(); class_index++)
		entropy += get_fuzzy_entropy(class_index, mu);

	return entropy;
}



float FuzzyClassiffication::get_fuzzy_entropy(unsigned int class_index, std::vector<std::vector<std::vector<float>>> &mu)
{
	float degree = 0.0f;
	float tmp_a = 0.0;
	float tmp_b = 0.0;

	for (unsigned int dataset_index = 0; dataset_index < mu.size(); dataset_index++)
		for (unsigned int i = 0; i < mu[dataset_index][class_index].size(); i++)
			tmp_a += mu[dataset_index][class_index][i];

	for (unsigned int dataset_index = 0; dataset_index < mu.size(); dataset_index++)
		for (unsigned int class_index_ = 0; class_index_ < mu[dataset_index].size(); class_index_++)
			for (unsigned int i = 0; i < mu[dataset_index][class_index_].size(); i++)
			{
				float tmp = mu[dataset_index][class_index_][i];
				tmp_b += tmp;
			}



	if (tmp_b > 0.0f)
	{
		degree = tmp_a / tmp_b;
	}

	printf("degree = %f\n", degree);
	/*
	// printf("%6.3f ", degree);
	if (tmp_b <= 0.0f)
		printf("\n error tmp_b = %f\n", tmp_b);

	if (degree <= 0.0f)
		printf("\n error degree = %f\n", degree);

	printf("\n tmp_b = %f\n", tmp_b/ mu.size());
*/

	if (degree <= 0.0f)
		return 0.0f;

	return -degree*log2f(degree);
}

